//
//  Mesh.cpp
//  OpenGLCourseApp
//
//  Created by Donya Hojabr on 2020-03-26.
//  Copyright © 2020 Donya Hojabr. All rights reserved.
//

#include "Mesh.hpp"
 
Mesh::Mesh(){
    
    VAO = 0;
    VBO = 0;
    IBO = 0;
    indexCount = 0;
}

void Mesh::createMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numIndices){
    indexCount = numIndices;
   
    glGenVertexArrays(1, &VAO); //storing ID of vertex array in VAO
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0])*numIndices, indices, GL_STATIC_DRAW);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0])*numOfVertices, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0])*5,0);//layout loc, sizeof each value passed in (x,y,z), type of value, normalize value (true/false), stride, offset)
    glEnableVertexAttribArray(0); //enable the 0 location in the array
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0])*5, (void*)(sizeof(vertices[0])*3));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0); //unbinding
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0); //unbinding
}

void Mesh::renderMesh(){
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::clearMesh(){
   
    if(IBO != 0){
        glDeleteBuffers(1,&IBO);
        IBO = 0;
    }
    if(VBO != 0){
        glDeleteBuffers(1,&VBO);
        VBO = 0;
    }
    if(VAO != 0){
        glDeleteVertexArrays(1,&VAO);
        VAO = 0;
    }
    indexCount = 0;
}
Mesh::~Mesh(){
    clearMesh();
}
