//
//  Camera.cpp
//  RayTracing1
//
//  Created by Daniel.Lin on 2019/9/17.
//  Copyright © 2019 Daniel.Lin. All rights reserved.
//

#include "Camera.hpp"
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera{
public:
    
    Camera(glm::vec3 _Pos, glm::vec3 _worldUp, float _pitch, float _yaw): Pos(_Pos),WorldUp(_worldUp), pitch(_pitch), yaw(_yaw)
    {
        UpdateCameraVectors();
    };
    
    glm::mat4 GetView(){return glm::lookAt(Pos, Pos+Front, Up);};
    
    ~Camera(){};
private:
    glm::vec3 Pos;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    
    float pitch; // -180~180
    float yaw; // -180~180
//    float roll;
    
    void UpdateCameraVectors(){
        glm::vec3 front;
        front.x=cos(glm::radians(pitch))*cos(glm::radians(yaw));
        front.y=sin(glm::radians(pitch));
        front.z=cos(glm::radians(pitch))*sin(glm::radians(yaw));
        Front=front;
        Right=glm::cross(Front, WorldUp);
        Up=glm::normalize(glm::cross(Right,WorldUp));
    }
    
};
