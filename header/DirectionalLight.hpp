
#include "Light.hpp"
#include "ext/vector_float3.hpp"

#pragma once
class DirectionalLight : public Light {
public:
  DirectionalLight();
  DirectionalLight(GLfloat shadowWidth, GLfloat shadowHeight, glm::vec3 RGB,
                   GLfloat ambient_intensity, glm::vec3 direction,
                   GLfloat diffuse_inytensity);
  void useDirectionalLight(GLuint ambient_intensity_location,
                           GLuint ambient_color_location,
                           GLuint Diffuse_intensity_location,
                           GLuint Direction_location);
  glm::mat4 calculateLightTransform();
  Shadowmap *getShadowmap() { return shadowmap; }

protected:
  glm::vec3 Direction;
  Shadowmap *shadowmap;

  glm::mat4 lightproj;
};
