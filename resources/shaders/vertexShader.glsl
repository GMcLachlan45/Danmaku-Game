#version 330 core
layout(location = 0) in vec4 position; // the position variable has attribute position 0
  
//out vec4 vertexColor; // sending color info to the frag shader

void main(){
    gl_Position = position; // see how we directly give a vec3 to vec4's constructor
//    vertexColor = vec4(1.0, 1.0, 1.0, 1.0);
}
