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
    
    for(size_t i = 0; i<1024; i++){
        keys[i] = 0;
    }
}

Window::Window(GLint windowWidth, GLint windowHeight){
    width = windowWidth;
    height = windowHeight;
    
    for(size_t i = 0; i<1024; i++){
        keys[i] = 0;
    }
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
    
    //Handles key presses
    createCallbacks();
    glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
    
    glfwSetWindowUserPointer(mainWindow, this);
    return 0;
}

void Window::createCallbacks(){
    glfwSetKeyCallback(mainWindow, handleKeys);
    glfwSetCursorPosCallback(mainWindow, handleMouse);
}

GLfloat Window::getXChange(){
    GLfloat theChange = xChange;
    xChange = 0;
    return theChange;
}

GLfloat Window::getYChange(){
    GLfloat theChange = yChange;
    yChange = 0;
    return theChange;
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode){ //no need to use static keyword, private variables need Window::
    
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if(key >= 0 && key < 1024){
        if(action == GLFW_PRESS){
            theWindow->keys[key]= true;
        }
        else if(action == GLFW_RELEASE){
            theWindow->keys[key]=false;
        }
    }
    
}

void Window::handleMouse(GLFWwindow *window, double xPos, double yPos){
    
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    
    if(theWindow->mouseFirstMoved){
        theWindow->lastX = xPos;
        theWindow->lastY = yPos;
        theWindow->mouseFirstMoved = false;
    }
    
    theWindow->xChange = xPos - theWindow->lastX;
    theWindow->yChange = theWindow->lastY - yPos;
    
    theWindow->lastX = xPos;
    theWindow->lastY = yPos;
    
}

Window::~Window(){
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}
