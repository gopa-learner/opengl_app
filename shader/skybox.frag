#version 460

out vec4 colour;
in vec3 Texcol;

uniform samplerCube skybox;

void main() {
    colour = texture(skybox, Texcol);
}
