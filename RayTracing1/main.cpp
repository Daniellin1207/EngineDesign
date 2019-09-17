//
//  main.cpp
//  RayTracing1
//
//  Created by Daniel.Lin on 2019/9/5.
//  Copyright © 2019 Daniel.Lin. All rights reserved.
//

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.hpp"
#include "Texture.hpp"
#include "ModelLoader.hpp"
#include "Camera.hpp"

void framebuffer_size_callback(GLFWwindow* window,int width,int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH=800;
const unsigned int SCR_HEIGHT=600;


int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
    
    GLFWwindow* window=glfwCreateWindow(800, 600, "LEHHL", NULL, NULL);
    if(window==NULL){
        std::cout<<"Failed"<<std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    

//    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    
    if(glewInit()!=GLEW_OK){
        std::cout<<"Init Failed!"<<std::endl;
        return -1;
    }
    
    ModelLoader model_cube("/Users/daniel/CodeManager/RayTracing1/RayTracing1/Models/sphereUv.obj");
    
    Shader test_shader("/Users/daniel/CodeManager/RayTracing1/RayTracing1/Shaders/test.vs",
                       "/Users/daniel/CodeManager/RayTracing1/RayTracing1/Shaders/test.fs");
    
    test_shader.SetInt("texture1", 1);
    Texture wall_texture("/Users/daniel/CodeManager/RayTracing1/RayTracing1/Textures/wall.jpg",false);
    
    wall_texture.BindTexture(1);
    
    while(!glfwWindowShouldClose(window)){
        
        processInput(window);
        
        glClearColor(0.2,0.3,0.5,1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        test_shader.Use();
        
        wall_texture.BindTexture(1);
        glBindVertexArray(model_cube.GetVAO());
        glDrawArrays(GL_TRIANGLES, 0, model_cube.GetSize());
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
};
