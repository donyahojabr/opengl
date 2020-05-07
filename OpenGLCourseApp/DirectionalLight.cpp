//
//  DirectionalLight.cpp
//  OpenGLCourseApp
//
//  Created by Donya Hojabr on 2020-05-07.
//  Copyright © 2020 Donya Hojabr. All rights reserved.
//

#include "DirectionalLight.hpp"

DirectionalLight::DirectionalLight() : Light(){ //calls super constructor first
    direction = glm::vec3(0.0f,-1.0f,0.0f);
}

DirectionalLight::DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity ){
    colour = glm::vec3(red,green,blue);
    ambientIntensity = aIntensity;
    direction = glm::vec3(xDir,yDir,zDir);
    diffuseIntensity = dIntensity;
}

void DirectionalLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation,GLuint diffuseIntensityLocation, GLuint directionLocation){
    glUniform3f(ambientColourLocation, colour.x,colour.y,colour.z);
    glUniform1f(ambientIntensityLocation, ambientIntensity);
    glUniform3f(directionLocation, direction.x,direction.y,direction.z);
    glUniform1f(diffuseIntensityLocation, diffuseIntensity);
}


