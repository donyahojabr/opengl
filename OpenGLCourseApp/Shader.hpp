//
//  Shader.hpp
//  OpenGLCourseApp
//
//  Created by Donya Hojabr on 2020-03-29.
//  Copyright © 2020 Donya Hojabr. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

#endif /* Shader_hpp */

class Shader{
public:
    Shader();
    
    void CreateFromString(const char* vertexCode, const char* fragmentCode);
    void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);
    
    std::string ReadFile(const char* fileLocation);
    
    GLuint GetProjectionLocation();
    GLuint GetModelLocation();
    GLuint GetViewLocation();
    GLuint GetAmbientIntensityLocation();
    GLuint GetAmbientColourLocation();
    GLuint GetDiffuseIntensityLocation();
    GLuint GetDirectionLocation();
    GLuint GetSpecularIntensityLocation();
    GLuint GetShininessLocation();
    GLuint GetEyePositionLocation();
    
    void UseShader();
    void clearShader();
    
    ~Shader();
    
private:
    GLuint shaderID, uniformProjection, uniformModel, uniformView, uniformEyePosition,
    uniformAmbientIntensity, uniformAmbientColour, uniformDiffuseIntensity, uniformDirection,
    uniformSpecularIntensity, uniformShininess;
    
    void CompileShader(const char* vertexCode, const char* fragmentCode);
    void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
    
};
