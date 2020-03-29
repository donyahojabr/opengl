#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector> //arraylists

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

#include "Mesh.hpp"
#include "Shader.hpp"

const GLint WIDTH = 800, HEIGHT = 600; //window dimensions
const float toRadians = 3.14159265f / 180.0f;

std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

bool direction = true; //right is true
float triOffset = 0.0f;
float triMaxOffset = 0.7f;
float triIncrement = 0.005f;

float curAngle = 0.0f;
bool sizeDirection = true;
float curSize = 0.4f;
float maxSize = 0.8f;
float minSize = 0.1f;

//Vertex shader
static const char* vShader = "shader.vs";

//fragment shader
static const char* fShader = "shader.fs";

void CreateObjects(){
    
    unsigned int indices[] = {
        0, 3, 1,
        1,3, 2,
        2, 3, 0,
        0, 1, 2
    };
    
    GLfloat vertices[] = {-1.0f,-1.0f,0.0f,
        0.0f, -1.0f, 1.0f, //will add depth to pyramid
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f }; //defining one triange

    Mesh *obj1 = new Mesh();
    obj1->createMesh(vertices, indices, 12, 12);
    meshList.push_back(obj1);
    
    Mesh *obj2 = new Mesh();
    obj2->createMesh(vertices, indices, 12, 12);
    meshList.push_back(obj2);
}

void CreateShaders(){
    Shader *shader1 = new Shader();
    shader1->CreateFromFiles(vShader, fShader);
    shaderList.push_back(*shader1);
    
}

int main(){
    if(!glfwInit( )){ //initialize glfw
        printf("GLFW initialization failed");
        glfwTerminate();
        return 1;
    }

    //window properties
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //version 3.x
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //version 3.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //won't let us use deprecated methods
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //allow forward compatibility
    //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


    //creating a window object
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL",  nullptr, nullptr);
    if(!window){
        printf("window creation failed");
        glfwTerminate();
        return 1;
    }

    int screenWidth, screenHeight;

    glfwGetFramebufferSize(window, &screenWidth, &screenHeight); //will talk about this later

    //ties this window to the code, so what we write goes to the correct window
    glfwMakeContextCurrent(window);

    //allows modern extension features
    glewExperimental = GL_TRUE;

    //initialize glew
    if(glewInit()!= GLEW_OK){
        printf("glew initialization failed");
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }
    
    glEnable(GL_DEPTH_TEST);

    //sets up the part of the window you draw to, so we set it to the buffer width and height
    glViewport(0, 0, screenWidth, screenHeight);

    CreateObjects();
    CreateShaders();
    
    glm::mat4 projection(1.0f);
    
    GLuint uniformProjection =0, uniformModel =0;
    projection = glm::perspective(45.0f, (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);

    //loop until window closed
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents(); //check for user inputs
        
        if(direction){
            triOffset += triIncrement;
        }
        else{
            triOffset -= triIncrement;
        }
        
        if(abs(triOffset) >= triMaxOffset){
            direction = !direction;
        }
        
        curAngle += 0.1f;
        
        if(curAngle >= 360){
            curAngle -=360;
        }
        
        if(sizeDirection){
            curSize += 0.001f;
        }
        else{
            curSize -= 0.001f;
        }
        if(curSize >= maxSize || curSize <= minSize){
            sizeDirection = !sizeDirection;
        }
        
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //clears entire screen, to color you set (red)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //tells what we want to clear, which is an or of the color and the depth buffer

        shaderList[0].UseShader();
        uniformModel = shaderList[0].GetModelLocation();
        uniformProjection = shaderList[0].GetProjectionLocation();
        
        glm::mat4 model(1.0f);
       
        model = glm::translate(model,glm::vec3(triOffset, 0.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f,0.4f,1.0));
      
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE,glm::value_ptr(model)); //false for transpose matrix
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE,glm::value_ptr(projection)); //false for transpose matrix
        meshList[0]->renderMesh();
        
        model = glm::mat4(1.0f);
        model = glm::translate(model,glm::vec3(-triOffset, 1.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f,0.4f,1.0));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE,glm::value_ptr(model)); //false for transpose matrix
        meshList[1]->renderMesh();
        
        glUseProgram(0);

        glfwSwapBuffers(window);

    }
    glfwTerminate();
    return 0;

}

