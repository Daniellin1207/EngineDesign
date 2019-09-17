//
//  ModelLoader.hpp
//  RayTracing1
//
//  Created by Daniel.Lin on 2019/9/15.
//  Copyright © 2019 Daniel.Lin. All rights reserved.
//

#ifndef ModelLoader_hpp
#define ModelLoader_hpp

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <stdio.h>


#include <string>
#include <iostream>
#include <vector>

struct Vertex{
    glm::vec3 pos;
    glm::vec2 texCoord;
    glm::vec3 color;
};

class ModelLoader{
public:
    ModelLoader(const GLchar* model_path);
    unsigned int GetVAO(){return VAO;};
    int GetSize(){return vertices.size();};
private:
    void SetupModel();
    unsigned int VAO,VBO,EBO;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
};

#endif /* ModelLoader_hpp */
