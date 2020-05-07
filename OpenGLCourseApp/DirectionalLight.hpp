//
//  DirectionalLight.hpp
//  OpenGLCourseApp
//
//  Created by Donya Hojabr on 2020-05-07.
//  Copyright © 2020 Donya Hojabr. All rights reserved.
//

#ifndef DirectionalLight_hpp
#define DirectionalLight_hpp

#include <stdio.h>
#include "Light.hpp"

#endif /* DirectionalLight_hpp */

class DirectionalLight :
    public Light
{
public:
    DirectionalLight();
    
    DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity);
    
    void UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation, GLuint diffuseIntensityLocation, GLuint directionLocation);
    
    ~DirectionalLight();

private:
    glm::vec3 direction;
};
