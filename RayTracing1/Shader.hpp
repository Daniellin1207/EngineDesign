//
//  Shader.hpp
//  RayTracing1
//
//  Created by Daniel.Lin on 2019/9/5.
//  Copyright © 2019 Daniel.Lin. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>
#include <string>
#include <GL/glew.h>

#include <fstream>
#include <sstream>
#include <iostream>

class Shader{
public:
    Shader(const GLchar* vs_path,const GLchar* fs_path);
    Shader(const GLchar* vs_path,const GLchar* gs_path,const GLchar* fs_path);
    void Use();
    int GetId(){return ID;};
    void SetFloat(const char* type_name, float value);
    void SetInt(const char* type_name, int value);
    ~Shader();

    int ID;
private:
    void checkCompileErrors(unsigned int shader,std::string type);
};

#endif /* Shader_hpp */
