#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

const GLint WIDTH = 800, HEIGHT = 600; //window dimensions
const float toRadians = 3.14159265f / 180.0f;

GLuint VAO, VBO, IBO,  shader, uniformModel, uniformProjection;

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
static const char* vShader = "                            \n\
#version 330                                              \n\
                                                          \n\
layout(location = 0) in vec3 pos;                         \n\
                                                          \n\
out vec4 vCol;                                            \n\
                                                          \n\
uniform mat4 model;                                       \n\
uniform mat4 projection;                                  \n\
                                                          \n\
void main()                                               \n\
{                                                         \n\
gl_Position = projection*model*vec4(pos,1.0);             \n\
vCol = vec4(clamp(pos, 0.0f, 1.0f),1.0f);                 \n\
}";

//fragment shader
static const char* fShader = "                      \n\
#version 330                                        \n\
                                                    \n\
in vec4 vCol;                                       \n\
                                                    \n\
out vec4 colour;                                    \n\
                                                    \n\
void main()                                         \n\
{                                                   \n\
colour = vCol;                                      \n\
}";

void CreateTriange(){
    
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

    glGenVertexArrays(1, &VAO); //storing ID of vertex array in VAO
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,0);//layout loc, sizeof each value passed in (x,y,z), type of value, normalize value (true/false), stride, offset)
    glEnableVertexAttribArray(0); //enable the 0 location in the array

    glBindBuffer(GL_ARRAY_BUFFER, 0); //unbinding
    glBindVertexArray(0); //unbinding
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType){
    GLuint theShader = glCreateShader(shaderType);
    const GLchar* theCode[1];
    theCode[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);

    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);

    if (!result){
        glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
        printf("Error compiling the %d program: '%s'\n",shaderType, eLog);
        return;
       }
    glAttachShader(theProgram, theShader);

}

void CompileShaders(){
    shader = glCreateProgram();
    if(!shader){
        printf("Error creating shader");
        return;
    }
    AddShader(shader, vShader, GL_VERTEX_SHADER);
    AddShader(shader, fShader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glLinkProgram(shader); //finsihed making the program
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if (!result){
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("Error linking program: '%s'\n", eLog);
        return;
    }

    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if (!result){
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("Error validating program: '%s'\n", eLog);
        //return;
    }
    
    uniformModel = glGetUniformLocation(shader, "model");
    uniformProjection = glGetUniformLocation(shader, "projection"); //name in shader
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

    CreateTriange();
    CompileShaders();
    
    glm::mat4 projection(1.0f);
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

        glUseProgram(shader);
        
        glm::mat4 model(1.0f);
       
        model = glm::translate(model,glm::vec3(0.0f, 0.0f, -2.5f));
        model = glm::rotate(model, curAngle*toRadians, glm::vec3(0.0f,1.0f,0.0f)); //last value is axis of rotation
        model = glm::scale(model, glm::vec3(0.4f,0.4f,1.0));
      
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE,glm::value_ptr(model)); //false for transpose matrix
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE,glm::value_ptr(projection)); //false for transpose matrix
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        glUseProgram(0);

        glfwSwapBuffers(window);

    }
    glfwTerminate();
    return 0;

}

