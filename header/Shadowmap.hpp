#pragma once
#include "Material.hpp"
#include <glm.hpp>

class Shadowmap {

protected:
  GLuint FBO, shadowmap, shadowHeight, shadowWidth;

public:
  Shadowmap();

  ~Shadowmap();
  virtual bool init(GLuint height, GLuint width);
  virtual void Write();
  virtual void Read(GLenum textureunit);
  GLuint Get_shadowWidth();
  GLuint Get_shadowHeight();
};
