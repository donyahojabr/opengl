//
//  Mesh.hpp
//  OpenGLCourseApp
//
//  Created by Donya Hojabr on 2020-03-26.
//  Copyright © 2020 Donya Hojabr. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <GL/glew.h>
#include <stdio.h>

#endif /* Mesh_hpp */

class Mesh{

public:
    Mesh();
    
    void createMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numIndices);
    void renderMesh();
    void clearMesh();
    ~Mesh();

private:
    GLuint VAO,VBO,IBO;
    GLsizei indexCount;
    
};
