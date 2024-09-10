#pragma once
#include "GL/glew.h"
#include "Shadowmap.hpp"
#include "fwd.hpp"
#include "glm/glm.hpp"
#include <iostream>

class Light {
protected:
  // light color
  glm::vec3 color = glm::vec3(1.0f);
  // internsity of different light

  GLfloat ambient_intensity = 1.0f, diffuse_intensity = 1.0f;

public:
  Light(glm::vec3 RGB, GLfloat Ambient_intensity, GLfloat Diffuse_intensity);
  Light();
  void UseLight(GLuint ambient_intensity_location,
                GLuint ambient_color_location,
                GLuint Diffuse_intensity_location);
  ~Light();
}

;
