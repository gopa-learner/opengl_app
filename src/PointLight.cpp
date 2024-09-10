#include "PointLight.hpp"
#include "OmniShadowmap.hpp"
#include "Shadowmap.hpp"
#include "ext/matrix_clip_space.hpp"
#include "ext/matrix_transform.hpp"
#include "ext/vector_float3.hpp"

PointLight::PointLight(GLfloat ShadowWidth, GLfloat ShadowHeight, glm::vec3 RGB,
                       GLfloat Ambient_intensity, GLfloat Diffuse_intensity,
                       glm::vec3 abc, glm::vec3 position, GLfloat near,
                       GLfloat far)
    : abc(abc), position(position), farplane(far),
      Light(RGB, Ambient_intensity, Diffuse_intensity) {

  float aspect = ShadowWidth / ShadowHeight;

  lightprooj = glm::perspective(glm::radians(90.0f), aspect, near, far);
  Shadowmap = new OmniShadowmap;

  Shadowmap->init(ShadowHeight, ShadowWidth);
}

PointLight::PointLight() : Light() {
  position = glm::vec3(0.0f, 0.0f, 0.0f);
  abc = glm::vec3(0.0f, 0.0f, 1.0f);
}

void PointLight::UsePointLight(GLuint ambient_intensity_location,
                               GLuint ambient_color_location,
                               GLuint Diffuse_intensity_location,
                               GLuint position_location,
                               GLuint exponent_location, GLuint Linear_location,
                               GLuint constant_location

) {

  UseLight(ambient_intensity_location, ambient_color_location,
           Diffuse_intensity_location);
  // for upadting unoform position
  //
  glUniform3f(position_location, position.x, position.y, position.z);

  glUniform1f(exponent_location, abc.x);

  glUniform1f(Linear_location, abc.y);

  glUniform1f(constant_location, abc.z);
}

PointLight::~PointLight() {}

std::array<glm::mat4, 6> PointLight::calculateLightTransform() {
  light_transform[0] =
      (lightprooj * glm::lookAt(position, position + glm::vec3(1.0, 0.0, 0.0),
                                glm::vec3(0.0, -1.0, 0.0)));

  light_transform[1] =
      (lightprooj * glm::lookAt(position, position + glm::vec3(-1.0, 0.0, 0.0),
                                glm::vec3(0.0, -1.0, 0.0)));

  light_transform[2] =
      (lightprooj * glm::lookAt(position, position + glm::vec3(0.0, 1.0, 0.0),
                                glm::vec3(0.0, 0.0, 1.0)));

  light_transform[3] =
      (lightprooj * glm::lookAt(position, position + glm::vec3(0.0, -1.0, 0.0),
                                glm::vec3(0.0, 0.0, -1.0)));

  light_transform[4] =
      (lightprooj * glm::lookAt(position, position + glm::vec3(0.0, 0.0, 1.0),
                                glm::vec3(0.0, -1.0, 0.0)));

  light_transform[5] =
      (lightprooj * glm::lookAt(position, position + glm::vec3(0.0, 0.0, -1.0),
                                glm::vec3(0.0, -1.0, 0.0)));

  return light_transform;
}

void PointLight::setposition(glm::vec3 pos) { this->position = pos; }
