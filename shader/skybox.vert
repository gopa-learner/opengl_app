#version 460

layout(location = 0) in vec3 pos;

out vec3 Texcol;
uniform mat4 projection;
uniform mat4 view;


void main()
{
    gl_Position = projection * view * vec4(pos.x, pos.y, pos.z, 1.0f);

    Texcol = pos;
}
