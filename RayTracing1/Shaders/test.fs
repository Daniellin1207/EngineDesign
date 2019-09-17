#version 330 core
out vec4 FragColor;
in vec2 Tex;
in vec3 Color;
uniform sampler2D texture1;

void main(){
//    FragColor=vec4(1.0f,Tex,1.0f);
//    FragColor=vec4(texture(texture1,Tex).rgb,1.0);
    FragColor=vec4(Color,1.0f);
}
