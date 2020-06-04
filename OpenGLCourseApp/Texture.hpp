//
//  Texture.hpp
//  OpenGLCourseApp
//
//  Created by Donya Hojabr on 2020-04-10.
//  Copyright © 2020 Donya Hojabr. All rights reserved.
//


#pragma once
#include <stdio.h>
#include <GL/glew.h>
#include "stb_image.h"

class Texture{
public:
    
    Texture();
    Texture(const char* fileLoc);
    
    bool LoadTexture();
    bool LoadTextureA();
    
    void UseTexture();
    void ClearTexture();
   
    ~Texture();
    
private:
    GLuint textureID;
    int width, height, bitDepth;
    
    const char* fileLocation;
};
