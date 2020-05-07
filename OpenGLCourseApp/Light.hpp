//
//  Light.hpp
//  OpenGLCourseApp
//
//  Created by Donya Hojabr on 2020-04-12.
//  Copyright © 2020 Donya Hojabr. All rights reserved.
//

#ifndef Light_hpp
#define Light_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#endif /* Light_hpp */

class Light{
public:
    Light();
    
    Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity);
    
    ~Light();
    
protected: //protected makes it accessible by subclasses
    glm::vec3 colour;
    GLfloat ambientIntensity;
    GLfloat diffuseIntensity;
};
