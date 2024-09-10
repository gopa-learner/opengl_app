#version 460

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 tex;
layout(location = 2) in vec3 normal;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 DirectionalLightTransform;



out vec4 vCol;
out vec2 Texcol;
out vec3 Normal;
out vec3 fragpos;
out vec4 DirectionalLightspacepos;
void main()
{
    gl_Position = projection * view * model * vec4(pos.x, pos.y, pos.z, 1.0f);
 DirectionalLightspacepos=DirectionalLightTransform*model*vec4(pos,1.0f);

    vCol = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);
    Texcol = tex;
    Normal = mat3(transpose(inverse(model))) * normal;

    fragpos = (model * vec4(pos, 1.0)).xyz;
}
