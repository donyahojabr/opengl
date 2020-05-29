//
//  PointLight.hpp
//  OpenGLCourseApp
//
//  Created by Donya Hojabr on 2020-05-26.
//  Copyright © 2020 Donya Hojabr. All rights reserved.
//
#pragma once

#include "Light.hpp" //don't need to include glew, etc. since it's in Light


class PointLight :
    public Light //extends Light
{
public:
    PointLight();
    PointLight(GLfloat red, GLfloat green, GLfloat blue,
               GLfloat aIntensity, GLfloat dIntensity,
               GLfloat xPos, GLfloat yPos, GLfloat zPos,
               GLfloat con, GLfloat lin, GLfloat exp);
    
    void UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation,
                  GLuint diffuseIntensityLocation, GLuint positionLocation,
                  GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation);

    ~PointLight();
    
protected:
    glm::vec3 position;
    GLfloat constant, linear, exponent; //used for quadratic attenutation/dropoff L/(ax^2 + bx + c)
};
