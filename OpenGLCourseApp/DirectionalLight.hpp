//
//  DirectionalLight.hpp
//  OpenGLCourseApp
//
//  Created by Donya Hojabr on 2020-05-07.
//  Copyright © 2020 Donya Hojabr. All rights reserved.
//
#pragma once

#include "Light.hpp"


class DirectionalLight :
    public Light
{
public:
    DirectionalLight();
    
    DirectionalLight(GLfloat red, GLfloat green, GLfloat blue,
                     GLfloat aIntensity, GLfloat dIntensity,
                     GLfloat xDir, GLfloat yDir, GLfloat zDir);
    
    void UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation, GLuint diffuseIntensityLocation, GLuint directionLocation);
    
//    ~DirectionalLight();

private:
    glm::vec3 direction;
};
