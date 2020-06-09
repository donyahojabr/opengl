//
//  ShadowMap.cpp
//  OpenGLCourseApp
//
//  Created by Donya Hojabr on 2020-06-09.
//  Copyright © 2020 Donya Hojabr. All rights reserved.
//

#include "ShadowMap.hpp"


ShadowMap::ShadowMap()
{
    FBO = 0;
    shadowMap = 0;
}

bool ShadowMap::Init(GLuint width, GLuint height)
{
    shadowWidth = width;
    shadowHeight = height;
    
    glGenFramebuffers(1, &FBO); //create one and pass ref to FBO
    
    glGenTextures(1, &shadowMap);
    glBindTexture(GL_TEXTURE_2D, shadowMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowWidth, shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr); //one big empty depthmap
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glBindFramebuffer(GL_FRAMEBUFFER, FBO); //binding this fbo id to the framebuffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap, 0); //saying we want fbo to write depth values only to tex
    
    glDrawBuffer(GL_NONE); //saying no colours drawn
    glReadBuffer(GL_NONE); //saying no colours read
    
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    
    if(status != GL_FRAMEBUFFER_COMPLETE)
    {
        printf("FBO error: %i\n", status);
        return false;
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0); //unbinding
    
    return true;
}

void ShadowMap::Write()
{
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}

void ShadowMap::Read(GLenum textureUnit)
{
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, shadowMap);
}

ShadowMap::~ShadowMap()
{
    if(FBO)
    {
        glDeleteFramebuffers(1, &FBO);
    }
    if(shadowMap)
    {
        glDeleteTextures(1, &shadowMap);
    }
}
