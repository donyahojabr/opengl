//
//  Material.cpp
//  OpenGLCourseApp
//
//  Created by Donya Hojabr on 2020-04-15.
//  Copyright © 2020 Donya Hojabr. All rights reserved.
//

#include "Material.hpp"

Material::Material(){
    specularIntensity = 0;
    shininess = 0;
}

Material::Material(GLfloat sIntensity, GLfloat shine){
    specularIntensity = sIntensity;
    shininess = shine;
}

void Material::UseMaterial(GLuint specularIntensityLocation, GLuint shininessLocation){
    glUniform1f(specularIntensityLocation, specularIntensity);
    glUniform1f(shininessLocation, shininess);
    
}

Material::~Material(){
    
}

