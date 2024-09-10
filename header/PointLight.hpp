#include "Light.hpp"
#include "Material.hpp"
#include "OmniShadowmap.hpp"
#include "ext/vector_float3.hpp"
#include "fwd.hpp"
#include <array>

#pragma once
class PointLight : public Light {

public:
  PointLight();
  ~PointLight();
  PointLight(GLfloat ShadowWidth, GLfloat ShadowHeight, glm::vec3 RGB,
             GLfloat Ambient_intensity, GLfloat Diffuse_intensity,
             glm::vec3 abc, glm::vec3 position, GLfloat near, GLfloat far);

  void UsePointLight(GLuint ambient_intensity_location,
                     GLuint ambient_color_location,
                     GLuint Diffuse_intensity_location,
                     GLuint position_location, GLuint exponent_location,
                     GLuint Linear_location, GLuint constant_location);

  void setposition(glm::vec3 pos);

  std::array<glm::mat4, 6> calculateLightTransform();
  GLfloat getfarplane() { return farplane; }
  glm::vec3 getPosition() { return position; }
  OmniShadowmap *getShadowmap() { return Shadowmap; }

protected:
  OmniShadowmap *Shadowmap;

  glm::vec3 position;
  glm::vec3 abc; /// for a*X^2+b*X+c
  ///
  ///
  GLfloat farplane;
  std::array<glm::mat4, 6> light_transform;

  glm::mat4 lightprooj;
};
