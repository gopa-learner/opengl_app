#pragma once

#include <GL/glew.h>
class Material {
private:
  GLfloat shininess = 0.0f, specularLighting_intensity = 0.0f;

public:
  Material();
  Material(GLfloat shininess, GLfloat specularLighting);
  void useMaterial(GLuint specularLighting_location, GLuint shininess_location);
};
