#pragma once
#include "Shadowmap.hpp"
#include <iostream>
class OmniShadowmap : public Shadowmap {

public:
  OmniShadowmap() {}
  ~OmniShadowmap() {}
  bool init(GLfloat height, GLfloat width);
  void Write();
  void Read(GLenum textureunit);
};
