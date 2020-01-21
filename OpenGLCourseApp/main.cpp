#include <iostream>
#include <stdio.h>

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

const GLint WIDTH = 800, HEIGHT = 600; //window dimensions

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
    };
    
    //sets up the part of the window you draw to, so we set it to the buffer width and height
    glViewport(0, 0, screenWidth, screenHeight);
    
    //loop until window closed
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents(); //check for user inputs
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f); //clears entire screen, to color you set (red)
        glClear(GL_COLOR_BUFFER_BIT); //tells what we want to clear, which is just the color (might be other stuff in there)
        glfwSwapBuffers(window); //
        
    }
    glfwTerminate();
    return 0;
    
}





