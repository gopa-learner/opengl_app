
#pragma once
#include "Light.hpp"
#include "PointLight.hpp"
#include "ext/vector_float3.hpp"

#include "geometric.hpp"
#include "trigonometric.hpp"

class Spotlight : public PointLight {
private:
  glm::vec3 direction;
  GLfloat edge, edgeangle;

public:
  Spotlight();
  ~Spotlight();
  void flashlight(glm::vec3 loc, glm::vec3 dir);

  Spotlight(GLfloat ShadowWidth, GLfloat ShadowHeight, glm::vec3 RGB,
            GLfloat Ambient_intensity, GLfloat Diffuse_intensity, glm::vec3 abc,
            glm::vec3 position, GLfloat edge, glm::vec3 direction, GLfloat near,
            GLfloat far);

  void UseSpotLight(GLuint ambient_intensity_location,
                    GLuint ambient_color_location,
                    GLuint Diffuse_intensity_location, GLuint position_location,
                    GLuint exponent_location, GLuint Linear_location,
                    GLuint constant_location, GLuint Direction_location,
                    GLuint edge_location);
};
