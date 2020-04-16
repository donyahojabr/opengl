//
//  Material.hpp
//  OpenGLCourseApp
//
//  Created by Donya Hojabr on 2020-04-15.
//  Copyright © 2020 Donya Hojabr. All rights reserved.
//

#ifndef Material_hpp
#define Material_hpp

#include <stdio.h>
#include <GL/glew.h>

#endif /* Material_hpp */

class Material{
    
public:
    Material();
    Material(GLfloat sIntensity, GLfloat shine);
    
    void UseMaterial(GLuint specularIntensityLocation, GLuint shininessLocation);
    
    ~Material();
    
private:
    GLfloat specularIntensity;
    GLfloat shininess; //concentration of specular highlight
    
    
};
