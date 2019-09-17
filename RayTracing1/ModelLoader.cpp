//
//  ModelLoader.cpp
//  RayTracing1
//
//  Created by Daniel.Lin on 2019/9/15.
//  Copyright © 2019 Daniel.Lin. All rights reserved.
//

#include "ModelLoader.hpp"

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "tiny_obj_loader.h"

ModelLoader::ModelLoader(const GLchar* model_path){
//    std::string inputfile = model_path;
    
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    
    std::string warn;
    std::string err;
    
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, model_path);
    
    if (!warn.empty()) {
        std::cout << warn << std::endl;
    }
    
    if (!err.empty()) {
        std::cerr << err << std::endl;
    }
    
    if (!ret) {
        exit(1);
    }
    

    for (const auto& shape : shapes)
    {
        for (const auto& index : shape.mesh.indices)
        {
            Vertex vertex = {};
            vertex.pos[0] = attrib.vertices[3 * index.vertex_index + 0];
            vertex.pos[1] = attrib.vertices[3 * index.vertex_index + 1];
            vertex.pos[2] = attrib.vertices[3 * index.vertex_index + 2];
            
            vertex.texCoord[0] = 0;//attrib.texcoords[2 * index.texcoord_index + 0];
            vertex.texCoord[1] = 0;//1.0f - attrib.texcoords[2 * index.texcoord_index + 1];
            
            vertex.color[0] = attrib.vertices[3*index.normal_index+0];
            vertex.color[1] = attrib.vertices[3*index.normal_index+1];
            vertex.color[2] = attrib.vertices[3*index.normal_index+2];
            
            vertices.push_back(vertex);
            indices.push_back(indices.size());
        }
    }
    SetupModel();
};

void ModelLoader::SetupModel(){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 &indices[0], GL_STATIC_DRAW);
    
    // 顶点位置
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
    // 顶点法线
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    // 顶点纹理坐标
    
    glBindVertexArray(0);
};
