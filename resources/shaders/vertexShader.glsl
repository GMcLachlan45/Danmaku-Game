#version 330 core
layout(location = 0) in vec3 position; // the position variable has attribute position 0
layout(location = 1) in vec3 inColor; // the color has attribute position 1
  
// here is where we will eventually import the matrix to move the thing around (mat3)

//out vec4 vertexColor; // sending color info to the frag shader

void main(){
    gl_Position = vec4(position, 1.0); // see how we directly give a vec3 to vec4's constructor mat * position
  //  vertexColor = vec4(0.0,1.0,1.0, 1.0);
}
