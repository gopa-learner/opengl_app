#version 330
in vec4 vCol;
out vec4 colour;
in vec2 Texcol;
uniform sampler2D theTexture;
void main() {
    colour = texture(theTexture, Texcol);
}
