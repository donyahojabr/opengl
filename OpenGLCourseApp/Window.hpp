//
//  Window.hpp
//  OpenGLCourseApp
//
//  Created by Donya Hojabr on 2020-03-30.
//  Copyright © 2020 Donya Hojabr. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#endif /* Window_hpp */

class Window{
public:
    Window();
    Window(GLint windowWidth, GLint windowHeight);
    
    int Initialise();
    
    GLfloat getBufferWidth() { return bufferWidth; }
    GLfloat getBUfferHeight() { return bufferHeight; }
    
    bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }
    
    void swapBuffers() { return glfwSwapBuffers(mainWindow); }
    
    ~Window();
    
private:
    GLFWwindow *mainWindow;
    GLint width, height;
    GLint bufferWidth, bufferHeight;
};

