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

void Model::RenderModel(){
    for(size_t i = 0; i < meshList.size(); i++){
        unsigned int matIndex = meshToTex[i];
        
        if(matIndex < textureList.size() && textureList[matIndex]){
            textureList[matIndex]->UseTexture();
        }
        meshList[i]->renderMesh();
    }
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

void Model::LoadMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<GLfloat> vertices;
    std::vector<unsigned int> indices;
    
    //populating the same way as main (pos, tex, norms)
    for(size_t i = 0; i < mesh->mNumVertices; i++){
        vertices.insert(vertices.end(), {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z});
        
        if(mesh->mTextureCoords[0]){ //if a texture exists
            vertices.insert(vertices.end(), {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y});
        }
        else {
            vertices.insert(vertices.end(), {0.0f, 0.0f});

        }
        vertices.insert(vertices.end(), {-mesh->mNormals[i].x, -mesh->mNormals[i].y, -mesh->mNormals[i].z});
    }
    //for each face go through the 3 points it contains and add them to indices list
    for(size_t i = 0; i < mesh->mNumFaces; i++){
        aiFace face = mesh->mFaces[i];
        for(size_t j = 0; j < face.mNumIndices; j++){
            indices.push_back(face.mIndices[j]);
        }
    }
    
    Mesh* newMesh = new Mesh();
    //vertices and indices start at 0th element, but this gets the whole thing
    newMesh->createMesh(&vertices[0], &indices[0], vertices.size(), indices.size());
    meshList.push_back(newMesh);
    meshToTex.push_back(mesh->mMaterialIndex); //need to say whether this mesh points to a texture
}

void Model::LoadMaterials(const aiScene *scene)
{
    textureList.resize(scene->mNumMaterials);
    
    for(size_t i = 0; i < scene->mNumMaterials; i++){
        aiMaterial* material = scene->mMaterials[i]; //if we find a texture here we'll put it in the same spot in texture list
        
        textureList[i] = nullptr;
        
        if(material->GetTextureCount(aiTextureType_DIFFUSE)){
            aiString path;
            if(material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == aiReturn_SUCCESS){
                //this is to remove absolute path if that exists, just want filename
//                int idx = std::string(path.data).rfind("\\");
                std::string thePath = &path.data[4];
                int idx = -1;
//                std::string filename = std::string(path.data).substr(idx + 1);
                std::string filename = thePath.substr(idx + 1);
                std::string texPath = std::string("Textures/") + filename;
                
                textureList[i] = new Texture(texPath.c_str());
                
                if(!textureList[i]->LoadTexture()){ //if load texture fails
                    printf("Failed to load texture at");
                    printf("HELLO %s",texPath.c_str());
                    delete textureList[i]; //calls deconstructor of Texture
                    textureList[i] = nullptr;
                }
            }
        }
        
        if(!textureList[i]){
            textureList[i] = new Texture("Textures/plain.png");
            textureList[i]->LoadTextureA(); //may need to remove A
        }
    }
    
}

void Model::ClearModel(){
    for(size_t i = 0; i < meshList.size(); i++){
        if(meshList[i]){
            delete meshList[i];
            meshList[i] = nullptr;
        }
    }
    
    for(size_t i = 0; i < textureList.size(); i++){
        if(textureList[i]){
            delete textureList[i];
            textureList[i] = nullptr;
        }
    }
}

Model::~Model()
{
    
}
