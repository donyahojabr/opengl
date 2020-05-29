////
////  Shader.hpp
////  OpenGLCourseApp
////
////  Created by Donya Hojabr on 2020-03-29.
////  Copyright © 2020 Donya Hojabr. All rights reserved.
////
//#pragma once
//
//#include <stdio.h>
//#include <string.h>
//#include <iostream>
//#include <fstream>
//
//#include "CommonValues.h"
//
//#include <GL/glew.h>
//#include "DirectionalLight.hpp"
//#include "PointLight.hpp"
//#include "SpotLight.hpp"
//
//
//class Shader{
//public:
//    Shader();
//
//    void CreateFromString(const char* vertexCode, const char* fragmentCode);
//    void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);
//
//    std::string ReadFile(const char* fileLocation);
//
//    GLuint GetProjectionLocation();
//    GLuint GetModelLocation();
//    GLuint GetViewLocation();
//    GLuint GetAmbientIntensityLocation();
//    GLuint GetAmbientColourLocation();
//    GLuint GetDiffuseIntensityLocation();
//    GLuint GetDirectionLocation();
//    GLuint GetSpecularIntensityLocation();
//    GLuint GetShininessLocation();
//    GLuint GetEyePositionLocation();
//
//    void setDirectionalLight(DirectionalLight * dLight);
//    void setPointLights(PointLight * pLight, unsigned int lightCount);
//    void setSpotLights(SpotLight * sLight, unsigned int lightCount);
//
//    void UseShader();
//    void clearShader();
//
//    ~Shader();
//
//private:
//
//    int pointLightCount; //we need this because each PL will have a uniformLoc
//    int spotLightCount;
//
//    GLuint shaderID, uniformProjection, uniformModel, uniformView, uniformEyePosition,
//    uniformSpecularIntensity, uniformShininess;
//
//    struct {
//        GLuint uniformColour;
//        GLuint uniformAmbientIntensity;
//        GLuint uniformDiffuseIntensity;
//
//        GLuint uniformDirection;
//    } uniformDirectionalLight; //instance of struct, not name
//
//    GLuint uniformPointLightCount;
//
//    struct {
//        GLuint uniformColour;
//        GLuint uniformAmbientIntensity;
//        GLuint uniformDiffuseIntensity;
//
//        GLuint uniformPosition;
//        GLuint uniformConstant;
//        GLuint uniformLinear;
//        GLuint uniformExponent;
//    } uniformPointLight[MAX_POINT_LIGHTS]; //need to have a max number
//
//    GLuint uniformSpotLightCount;
//
//    struct {
//        GLuint uniformColour;
//        GLuint uniformAmbientIntensity;
//        GLuint uniformDiffuseIntensity;
//
//        GLuint uniformPosition;
//        GLuint uniformConstant;
//        GLuint uniformLinear;
//        GLuint uniformExponent;
//
//        GLuint uniformDirection;
//        GLuint uniformEdge;
//    } uniformSpotLight[MAX_SPOT_LIGHTS];
//
//    void CompileShader(const char* vertexCode, const char* fragmentCode);
//    void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
//
//};

#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

#include "CommonValues.h"

#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "SpotLight.hpp"

class Shader
{
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

    void setDirectionalLight(DirectionalLight * dLight);
    void setPointLights(PointLight * pLight, unsigned int lightCount);
    void setSpotLights(SpotLight * sLight, unsigned int lightCount);

    void UseShader();
    void ClearShader();

    ~Shader();

private:
    int pointLightCount;
    int spotLightCount;

    GLuint shaderID, uniformProjection, uniformModel, uniformView, uniformEyePosition,
        uniformSpecularIntensity, uniformShininess;

    struct {
        GLuint uniformColour;
        GLuint uniformAmbientIntensity;
        GLuint uniformDiffuseIntensity;

        GLuint uniformDirection;
    } uniformDirectionalLight;

    GLuint uniformPointLightCount;

    struct {
        GLuint uniformColour;
        GLuint uniformAmbientIntensity;
        GLuint uniformDiffuseIntensity;

        GLuint uniformPosition;
        GLuint uniformConstant;
        GLuint uniformLinear;
        GLuint uniformExponent;
    } uniformPointLight[MAX_POINT_LIGHTS];

    GLuint uniformSpotLightCount;

    struct {
        GLuint uniformColour;
        GLuint uniformAmbientIntensity;
        GLuint uniformDiffuseIntensity;

        GLuint uniformPosition;
        GLuint uniformConstant;
        GLuint uniformLinear;
        GLuint uniformExponent;

        GLuint uniformDirection;
        GLuint uniformEdge;
    } uniformSpotLight[MAX_SPOT_LIGHTS];

    void CompileShader(const char* vertexCode, const char* fragmentCode);
    void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};


