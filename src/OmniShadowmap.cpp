#include "OmniShadowmap.hpp"
#include "Light.hpp"
#include "Material.hpp"

bool OmniShadowmap::init(GLfloat height, GLfloat width) {

  shadowWidth = width;
  shadowHeight = height;
  glGenFramebuffers(1, &FBO);
  glGenTextures(1, &shadowmap);
  glBindTexture(GL_TEXTURE_CUBE_MAP, shadowmap);
  for (size_t i = 0; i < 6; i += 1) {
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT,
                 shadowWidth, shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT,
                 nullptr);
  }
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  glBindFramebuffer(GL_FRAMEBUFFER, FBO);
  glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowmap, 0);
  glDrawBuffer(GL_NONE);
  glReadBuffer(GL_NONE);
  GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if (Status != GL_FRAMEBUFFER_COMPLETE) {
    std::cerr << "Framebuffer error: " << Status;
    return false;
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  return true;
}

void OmniShadowmap::Write() { glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO); }

void OmniShadowmap::Read(GLenum texUnit) {
  glActiveTexture(texUnit);
  glBindTexture(GL_TEXTURE_CUBE_MAP, shadowmap);
}
