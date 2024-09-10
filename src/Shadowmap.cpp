#include "Shadowmap.hpp"
#include "Light.hpp"
#include "Material.hpp"
#include "utilities.hpp"
bool Shadowmap::init(GLuint width, GLuint height) {
  shadowWidth = width, shadowHeight = height;

  glGenFramebuffers(1, &FBO);
  glGenTextures(1, &shadowmap);
  glBindTexture(GL_TEXTURE_2D, shadowmap);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowWidth, shadowHeight,
               0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

  GLfloat bcolor[] = {1.0f, 1.0f, 1.0f, 1.0f};

  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, bcolor);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glBindFramebuffer(GL_FRAMEBUFFER, FBO);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
                         shadowmap, 0);

  glDrawBuffer(GL_NONE);

  glReadBuffer(GL_NONE);

  if (get_error(GL_FRAMEBUFFER)) {
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    return true;
  } else
    return false;
}

void Shadowmap::Write() { glBindFramebuffer(GL_FRAMEBUFFER, FBO); }

void Shadowmap::Read(GLenum textureunit) {

  glActiveTexture(textureunit);
  glBindTexture(GL_TEXTURE_2D, shadowmap);
}

Shadowmap::~Shadowmap() {

  if (FBO)
    glDeleteFramebuffers(1, &FBO);

  if (shadowmap)
    glDeleteTextures(1, &shadowmap);
}
Shadowmap::Shadowmap() {}

GLuint Shadowmap::Get_shadowWidth() { return shadowWidth; }
GLuint Shadowmap::Get_shadowHeight() { return shadowHeight; }
