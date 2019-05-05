#version 330 core
layout (location = 0) in vec3 aPos;         // position at attribute position 0

uniform mat4 world;
uniform mat4 view;
uniform mat4 proj;
        
void main()
{
    gl_Position = proj * view * vec4(aPos, 1.0f);
    //gl_Position = vec4(aPos.x, aPos.y, 0.0f, 1.0f);
}