#pragma once

#include "GL/glew.h"
#include "stb_image.h"
#include <iostream>
#include <string>
class Texture {

private:
  GLuint Texture_id{0};
  int Width{0}, Height{0}, Bitdepth{0};
  std::string filelocation{};

public:
  Texture(std::string fileLocation);
  Texture();
  ~Texture();

  void Load_texture();
  void Use_tetxtue();
  void Clear_texture();
};
