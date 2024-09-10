#include "Spotlight.hpp"

Spotlight::Spotlight(GLfloat ShadowWidth, GLfloat ShadowHeight, glm::vec3 RGB,
                     GLfloat Ambient_intensity, GLfloat Diffuse_intensity,
                     glm::vec3 abc, glm::vec3 position, GLfloat edge,
                     glm::vec3 direction, GLfloat near, GLfloat far)
    : PointLight(ShadowWidth, ShadowHeight, RGB, Ambient_intensity,
                 Diffuse_intensity, abc, position, near, far),
      edge(edge) {
  this->direction = glm::normalize(direction);
  edgeangle = std::cosf(glm::radians(this->edge));
}

Spotlight::Spotlight() : PointLight() {
  direction = glm::vec3(0.0f, -1.0f, 0.0f);
  edge = 0.0f;
}

void Spotlight::UseSpotLight(GLuint ambient_intensity_location,
                             GLuint ambient_color_location,
                             GLuint Diffuse_intensity_location,
                             GLuint position_location, GLuint exponent_location,
                             GLuint Linear_location, GLuint constant_location,
                             GLuint Direction_location, GLuint edge_location) {

  UsePointLight(ambient_intensity_location, ambient_color_location,
                Diffuse_intensity_location, position_location,
                exponent_location, Linear_location, constant_location);

  glUniform3f(Direction_location, direction.x, direction.y, direction.z);

  glUniform1f(edge_location, edgeangle);
}

Spotlight::~Spotlight() {}

void Spotlight::flashlight(glm::vec3 loc, glm::vec3 dir) {

  this->position = loc;
  this->direction = dir;
}
