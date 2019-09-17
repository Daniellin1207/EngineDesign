//
//  Shader.cpp
//  RayTracing1
//
//  Created by Daniel.Lin on 2019/9/5.
//  Copyright © 2019 Daniel.Lin. All rights reserved.
//

#include "Shader.hpp"


Shader::Shader(const GLchar* vs_path,const GLchar* fs_path){

    std::string vertCode;
    std::string fragCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try{
        vShaderFile.open(vs_path);
        fShaderFile.open(fs_path);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream<<vShaderFile.rdbuf();
        fShaderStream<<fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertCode=vShaderStream.str();
        fragCode=fShaderStream.str();
    }catch(std::ifstream::failure e){
        std::cout<<"ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ"<<std::endl;
    }
    const char* vShaderCode=vertCode.c_str();
    const char* fShaderCode=fragCode.c_str();

    unsigned int vert,frag;

    vert=glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert,1,&vShaderCode,NULL);
    glCompileShader(vert);
    checkCompileErrors(vert, "VERTEX");

    frag=glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag,1,&fShaderCode,NULL);
    glCompileShader(frag);
    checkCompileErrors(frag, "FRAGMENT");

    ID=glCreateProgram();
    glAttachShader(ID,vert);
    glAttachShader(ID,frag);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    glDeleteShader(vert);
    glDeleteShader(frag);

};

void Shader::Use(){
    glUseProgram(this->ID);
};


Shader::~Shader(){

};

void Shader::checkCompileErrors(unsigned int shader, std::string type){
    int success;
    char infoLog[1024];
    if(type!="PROGRAM"){
        glGetShaderiv(shader,GL_COMPILE_STATUS,&success);
        if(!success){
            glGetShaderInfoLog(shader,1024,NULL,infoLog);
            std::cout<<"ERROR::SHADER_COMPILATION_ERROR of type: "<<type<<"\n"<<infoLog<<"\n";
        }
    }else{
        glGetProgramiv(shader,GL_LINK_STATUS,&success);
        if(!success){
            glGetProgramInfoLog(shader,1024,NULL,infoLog);
            std::cout<<"ERROR::SHADER_LINKING_ERROR of type: "<<type<<"\n"<<infoLog<<"\n";
        }
    }
}

void Shader::SetFloat(const char* type_name, float value){
    glUniform1f(glGetUniformLocation(ID, type_name), value);
};
void Shader::SetInt(const char* type_name, int value){
    glUniform1i(glGetUniformLocation(ID, type_name), value);
};
