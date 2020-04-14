#define STB_IMAGE_IMPLEMENTATION

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
#include "Camera.hpp"
#include "Texture.hpp"
#include "Light.hpp"

//const float toRadians = 3.14159265f / 180.0f;

std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;
Window mainWindow;
Camera camera;
Light mainLight;

Texture brickTexture;
Texture dirtTexture;

GLfloat delatTime = 0.0f;
GLfloat lastTime = 0.0f;

//Vertex shader
static const char* vShader = "Shader/shader.vs";

//fragment shader
static const char* fShader = "Shader/shader.fs";

void calcNormals(unsigned int * indices, unsigned int indiceCount, GLfloat * vertices, unsigned int verticeCount, unsigned int vLength, unsigned normalOffset){
    
    for(size_t i = 0; i < indiceCount; i+=3){
        unsigned int in0 = indices[i] * vLength;
        unsigned int in1 = indices[i+1]*vLength;
        unsigned int in2 = indices[i+2]*vLength;
        glm::vec3 v1 (vertices[in1]-vertices[in0],vertices[in1+1]-vertices[in0+1], vertices[in1+2]-vertices[in0+2]);
        glm::vec3 v2 (vertices[in2]-vertices[in0],vertices[in2+1]-vertices[in0+1], vertices[in2+2]-vertices[in0+2]);
        glm::vec3 normal = glm::normalize(glm::cross(v1,v2));
        
        in0 += normalOffset;
        in1 += normalOffset;
        in2 += normalOffset;
        vertices[in0] += normal.x;
        vertices[in0+1] += normal.y;
        vertices[in0+2] += normal.z;
        vertices[in1] += normal.x;
        vertices[in1+1] += normal.y;
        vertices[in1+2] += normal.z;
        vertices[in2] += normal.x;
        vertices[in2+1] += normal.y;
        vertices[in2+2] += normal.z;
    }
    
    for(size_t i =0; i<verticeCount/vLength; i++){
        unsigned int nOffset = i*vLength+nOffset;
        glm::vec3 vec(vertices[nOffset],vertices[nOffset+1],vertices[nOffset+2]);
        vec = glm::normalize(vec);
        vertices[nOffset] = vec.x;
        vertices[nOffset+1] = vec.y;
        vertices[nOffset+2] = vec.z;
        
    }
}

void CreateObjects(){
    
    unsigned int indices[] = {
        0, 3, 1,
        1,3, 2,
        2, 3, 0,
        0, 1, 2
    };
    
    GLfloat vertices[] = {
        //x     y       z       u       v       nx     ny   nz
        -1.0f,-1.0f,0.0f,       0.0f,   0.0f,   0.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 1.0f,      0.5f,   0.0f,   0.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 0.0f,      1.0f,   0.0f,   0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,       0.5f,   1.0f,    0.0f, 0.0f, 0.0f
        
    };
    
    calcNormals(indices, 12, vertices, 32, 8, 5);

    Mesh *obj1 = new Mesh();
    obj1->createMesh(vertices, indices, 32, 12);
    meshList.push_back(obj1);
    
    Mesh *obj2 = new Mesh();
    obj2->createMesh(vertices, indices, 32, 12);
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
    camera = Camera(glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f), -90.0f,0.0f,5.0f,0.08f);
    
    brickTexture = Texture("Textures/wall.png");
    brickTexture.LoadTexture();
    dirtTexture = Texture("Textures/sky.png");
    dirtTexture.LoadTexture();
    
    mainLight = Light(1.0f,1.0f,1.0f,0.2f,
                      2.0f,-1.0f,-2.0f,1.0f);
    
    
    glm::mat4 projection(1.0f);
    
    GLuint uniformProjection =0, uniformModel =0, uniformView = 0, uniformAmbientIntensity = 0, uniformAmbientColour = 0, uniformDirection =0, uniformDiffuseIntensity =0;
    projection = glm::perspective(45.0f, (float)mainWindow.getBufferWidth()/(float)mainWindow.getBUfferHeight(), 0.1f, 100.0f);

    //loop until window closed
    while(!mainWindow.getShouldClose()){
        
        GLfloat now = glfwGetTime();
        delatTime = now - lastTime;
        lastTime = now;
        
        glfwPollEvents(); //check for user inputs
        camera.keyControl(mainWindow.getKeys(), delatTime);
        camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
        
        
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //clears entire screen, to color you set (red)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //tells what we want to clear, which is an or of the color and the depth buffer

        shaderList[0].UseShader();
        uniformModel = shaderList[0].GetModelLocation();
        uniformProjection = shaderList[0].GetProjectionLocation();
        uniformView = shaderList[0].GetViewLocation();
        uniformAmbientColour = shaderList[0].GetAmbientColourLocation();
        uniformAmbientIntensity = shaderList[0].GetAmbientIntensityLocation();
        uniformDirection = shaderList[0].GetDirectionLocation();
        uniformDiffuseIntensity = shaderList[0].GetDiffuseIntensityLocation();
        
        mainLight.UseLight(uniformAmbientIntensity, uniformAmbientColour, uniformDiffuseIntensity, uniformDirection);
        
        glm::mat4 model(1.0f);
       
        model = glm::translate(model,glm::vec3(0.0f, 0.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f,0.4f,1.0));
      
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE,glm::value_ptr(model)); //false for transpose matrix
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE,glm::value_ptr(projection)); //false for transpose matrix
        glUniformMatrix4fv(uniformView, 1, GL_FALSE,glm::value_ptr(camera.calculateViewMatrix())); //false for transpose matrix
        
        brickTexture.UseTexture();
        meshList[0]->renderMesh();
        
        model = glm::mat4(1.0f);
        model = glm::translate(model,glm::vec3(0.0f, 1.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f,0.4f,1.0));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE,glm::value_ptr(model)); //false for transpose matrix
        
        dirtTexture.UseTexture();
        meshList[1]->renderMesh();
        
        glUseProgram(0);

        mainWindow.swapBuffers();

    }
    glfwTerminate();
    return 0;

}

