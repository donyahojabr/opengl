//
//  Model.cpp
//  OpenGLCourseApp
//
//  Created by Donya Hojabr on 2020-06-03.
//  Copyright © 2020 Donya Hojabr. All rights reserved.
//

#include "Model.hpp"

Model::Model()
{
    
}

void Model::LoadModel(const std::string& filename)
{
    Assimp::Importer importer;
    //flipUVs flips all tex coords around y axis, smoothNormals for interpolation, 2 vert at some point treated as one
    const aiScene *scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices); //triangulate forces shapes to be made into tris
    
    if(!scene){
        printf("Model failed to load: %s",importer.GetErrorString());
        return;
    }
    
    LoadNode(scene->mRootNode, scene); //mrootnode is first node that encompasses all
    LoadMaterials(scene);
}

void Model::LoadNode(aiNode *node, const aiScene *scene)
{
    for(size_t i = 0; i<node->mNumMeshes; i++){
        LoadMesh(scene->mMeshes[node->mMeshes[i]], scene);
    }
    for(size_t i = 0; i<node->mNumChildren; i++){
        LoadNode(node->mChildren[i], scene);
    }
}

Model::~Model()
{
    
}
