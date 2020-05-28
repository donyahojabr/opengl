//
//  PointLight.cpp
//  OpenGLCourseApp
//
//  Created by Donya Hojabr on 2020-05-26.
//  Copyright © 2020 Donya Hojabr. All rights reserved.
//

#include "PointLight.hpp"

PointLight::PointLight() : Light()
{
    position = glm::vec3(0.0f,0.0f,0.0f);
    constant = 1.0f; //to ensure we don't divide by 0
    linear = 0.0f;
    exponent = 0.0f;
}

PointLight::PointLight(GLfloat red, GLfloat green, GLfloat blue,
                       GLfloat aIntensity, GLfloat dIntensity,
                       GLfloat xPos, GLfloat yPos, GLfloat zPos,
                       GLfloat con, GLfloat lin, GLfloat exp) : Light(red, green, blue, aIntensity, dIntensity)
{
    position = glm::vec3(xPos,yPos,zPos);
    constant = con;
    linear = lin;
    exponent = exp;
}

void PointLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation,
              GLuint diffuseIntensityLocation, GLuint positionLocation,
              GLfloat constantLocation, GLfloat linearLocation, GLfloat exponentLocation)
{
    glUniform3f(ambientColourLocation, colour.x,colour.y,colour.z);
    glUniform1f(ambientIntensityLocation, ambientIntensity);
    glUniform1f(diffuseIntensityLocation, diffuseIntensity);
    
    glUniform3f(positionLocation, position.x, position.y, position.z);
    glUniform1f(constantLocation, constant);
    glUniform1f(linearLocation, linear);
    glUniform1f(exponentLocation, exponent);


}

PointLight::~PointLight()
{
    
}