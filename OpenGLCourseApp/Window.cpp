//
//  Window.cpp
//  OpenGLCourseApp
//
//  Created by Donya Hojabr on 2020-03-30.
//  Copyright © 2020 Donya Hojabr. All rights reserved.
//

#include "Window.hpp"

Window::Window(){
    width = 800;
    height = 600;
}

Window::Window(GLint windowWidth, GLint windowHeight){
    width = windowWidth;
    height = windowHeight;
}

int Window::Initialise(){
    
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
    mainWindow = glfwCreateWindow(width, height, "Learn OpenGL",  nullptr, nullptr);
    if(!mainWindow){
        printf("window creation failed");
        glfwTerminate();
        return 1;
    }

    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    //ties this window to the code, so what we write goes to the correct window
    glfwMakeContextCurrent(mainWindow);

    //allows modern extension features
    glewExperimental = GL_TRUE;

    //initialize glew
    if(glewInit()!= GLEW_OK){
        printf("glew initialization failed");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }
    
    glEnable(GL_DEPTH_TEST);

    //sets up the part of the window you draw to, so we set it to the buffer width and height
    glViewport(0, 0, bufferWidth, bufferHeight);
    return 0;
}

Window::~Window(){
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}
