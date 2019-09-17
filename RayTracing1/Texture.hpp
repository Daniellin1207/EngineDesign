//
//  Texture.hpp
//  RayTracing1
//
//  Created by Daniel.Lin on 2019/9/6.
//  Copyright © 2019 Daniel.Lin. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <iostream>


class Texture{
public:
    Texture(const GLchar* texture_path, bool vertical=false);
    void SetMode();
    void BindTexture(unsigned int i);
    ~Texture(){};
private:
    unsigned int texture;
};


#endif /* Texture_hpp */
