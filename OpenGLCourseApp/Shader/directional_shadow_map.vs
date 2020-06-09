#version 330

layout (location = 0) in vec3 pos;

uniform mat4 model;
uniform mat4 directionalLightSpaceTransform; //convert pos to light's perspective

void main()
{
    gl_Position = directionalLightSpaceTransform * model * vec4(pos, 1.0); //will gen depth map for us
}
