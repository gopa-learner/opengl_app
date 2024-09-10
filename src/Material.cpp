

#include "Material.hpp"

Material::Material() {}

Material::Material(GLfloat shininess, GLfloat specularLighting)
    : shininess(shininess), specularLighting_intensity(specularLighting) {}
void Material::useMaterial(GLuint specularLighting_location,
                           GLuint shininess_location) {

  glUniform1f(specularLighting_location, specularLighting_intensity);
  glUniform1f(shininess_location, shininess);
}
