//
//  Texture.hpp
//  OpenGLCourseApp
//
//  Created by Donya Hojabr on 2020-04-10.
//  Copyright © 2020 Donya Hojabr. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <stdio.h>
#include <GL/glew.h>
#include "stb_image.h"

#endif /* Texture_hpp */

class Texture{
public:
    
    Texture();
    Texture(char* fileLoc);
    
    void LoadTexture();
    void UseTexture();
    void ClearTexture();
   
    ~Texture();
    
private:
    GLuint textureID;
    int width, height, bitDepth;
    
    char* fileLocation;
};
