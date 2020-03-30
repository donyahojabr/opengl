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
#include "Window.hpp"

const float toRadians = 3.14159265f / 180.0f;

std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;
Window mainWindow;

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

    mainWindow = Window();
    mainWindow.Initialise();
    
    CreateObjects();
    CreateShaders();
    
    glm::mat4 projection(1.0f);
    
    GLuint uniformProjection =0, uniformModel =0;
    projection = glm::perspective(45.0f, (float)mainWindow.getBufferWidth()/(float)mainWindow.getBUfferHeight(), 0.1f, 100.0f);

    //loop until window closed
    while(!mainWindow.getShouldClose()){
        glfwPollEvents(); //check for user inputs
        
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //clears entire screen, to color you set (red)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //tells what we want to clear, which is an or of the color and the depth buffer

        shaderList[0].UseShader();
        uniformModel = shaderList[0].GetModelLocation();
        uniformProjection = shaderList[0].GetProjectionLocation();
        
        glm::mat4 model(1.0f);
       
        model = glm::translate(model,glm::vec3(0.0f, 0.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f,0.4f,1.0));
      
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE,glm::value_ptr(model)); //false for transpose matrix
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE,glm::value_ptr(projection)); //false for transpose matrix
        meshList[0]->renderMesh();
        
        model = glm::mat4(1.0f);
        model = glm::translate(model,glm::vec3(0.0f, 1.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f,0.4f,1.0));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE,glm::value_ptr(model)); //false for transpose matrix
        meshList[1]->renderMesh();
        
        glUseProgram(0);

        mainWindow.swapBuffers();

    }
    glfwTerminate();
    return 0;

}

