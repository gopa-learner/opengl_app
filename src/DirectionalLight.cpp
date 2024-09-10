#include "DirectionalLight.hpp"
#include "Shadowmap.hpp"
#include "ext/matrix_clip_space.hpp"
#include "ext/matrix_transform.hpp"
#include "ext/vector_float3.hpp"
#include "geometric.hpp"
DirectionalLight::DirectionalLight(GLfloat shadowWidth, GLfloat shadowHeight,
                                   glm::vec3 RGB, GLfloat Ambient_intensity,
                                   glm::vec3 direction,
                                   GLfloat Diffuse_intensity)
    : Light(RGB, Ambient_intensity, Diffuse_intensity) {
  this->Direction = glm::normalize(direction);

  shadowmap = new Shadowmap;
  shadowmap->init(shadowHeight, shadowWidth);

  lightproj = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f);
}
DirectionalLight::DirectionalLight() : Light() { Direction = glm::vec3(1.0f); }

void DirectionalLight::useDirectionalLight(GLuint ambient_intensity_location,
                                           GLuint ambient_color_location,
                                           GLuint Diffuse_intensity_location,
                                           GLuint Direction_location) {

  UseLight(ambient_intensity_location, ambient_color_location,
           Diffuse_intensity_location);

  glUniform3f(Direction_location, Direction.x, Direction.y, Direction.z);
}

glm::mat4 DirectionalLight::calculateLightTransform() {

  return (lightproj * glm::lookAt(-Direction, glm::vec3(0.0f, 0.0f, 0.0f),
                                  glm::vec3(0.0f, 1.0f, 0.0f)));
}
