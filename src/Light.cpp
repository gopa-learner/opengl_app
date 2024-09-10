#include "Light.hpp"
#include "Shadowmap.hpp"
#include "ext/vector_float3.hpp"
Light::Light(glm::vec3 RGB, GLfloat Ambient_intensity,
             GLfloat Diffuse_intensity)
    : color(RGB), ambient_intensity(Ambient_intensity),
      diffuse_intensity(Diffuse_intensity) {}
Light::Light() {

  color = glm::vec3(1.0f, 1.0f, 1.0f);
  ambient_intensity = 1.0f;
  diffuse_intensity = 1.0f;
}

void Light::UseLight(GLuint ambient_intensity_location,
                     GLuint ambient_color_location,
                     GLuint Diffuse_intensity_location) {
  // diffuse Light
  glUniform1f(Diffuse_intensity_location, diffuse_intensity);
  // ambient light
  glUniform3f(ambient_color_location, color.x, color.y, color.z);
  glUniform1f(ambient_intensity_location, ambient_intensity);
}
Light::~Light() {}
