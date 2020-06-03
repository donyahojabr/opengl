//
//  Model.hpp
//  OpenGLCourseApp
//
//  Created by Donya Hojabr on 2020-06-03.
//  Copyright © 2020 Donya Hojabr. All rights reserved.
//

#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.hpp"
#include "Texture.hpp"

#include <vector>
#include <string>


class Model {
public:
    Model();
    
    void LoadModel(const std::string& filename);
    void RenderModel();
    void ClearModel();
    
    ~Model();
    
private:
    void LoadNode(aiNode *node, const aiScene *scene);
    void LoadMesh(aiMesh *mesh, const aiScene *scene);
    void LoadMaterials(const aiScene *scene);
    std::vector<Mesh*> meshList;
    std::vector<Texture*> textureList;
    std::vector<unsigned int> meshToTex;
};
