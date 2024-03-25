
#include "Texture.hpp"

Texture::Texture(std::string fileLoction) { filelocation = fileLoction; }
Texture::Texture() {}

Texture::~Texture() { Clear_texture(); }
void Texture::Load_texture() {

  unsigned char *textData =
      stbi_load(filelocation.c_str(), &Width, &Height, &Bitdepth, 0);
  if (!textData) {
    std::cout << "failed to find data at \n " << filelocation;
    return;
  }
  glGenTextures(1, &Texture_id);

  glBindTexture(GL_TEXTURE_2D, Texture_id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, textData);
  glGenerateMipmap(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE0, 0);
  glBindTexture(GL_TEXTURE_2D, 0);
  stbi_image_free(textData);
}
void Texture::Use_tetxtue() {

  // glBindTexture(GL_TEXTURE0, Texture_id);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, Texture_id);
}

void Texture::Clear_texture() {

  glDeleteTextures(1, &Texture_id);
  Texture_id = Width = Height = Bitdepth = 0;
  filelocation = "";
}
