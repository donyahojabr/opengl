//
//  Light.cpp
//  OpenGLCourseApp
//
//  Created by Donya Hojabr on 2020-04-12.
//  Copyright © 2020 Donya Hojabr. All rights reserved.
//

#include "Light.hpp"

Light::Light(){
    colour = glm::vec3(1.0f,1.0f,1.0f); //these represent how much of each channel will be shown (1.0 = full colour)
    ambientIntensity = 1.0f;
    diffuseIntensity = 0.0f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity ){
    colour = glm::vec3(red,green,blue);
    ambientIntensity = aIntensity;
    diffuseIntensity = dIntensity;
}

Light::~Light(){
    
}
