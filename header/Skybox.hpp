
#pragma once

#include <string>
#include <vector>

#include "constants.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.hpp"
#include "Shader.hpp"

class Skybox {
public:
  Skybox();

  Skybox(std::vector<std::string> faceLocations);

  void DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

  ~Skybox();

private:
  Mesh *skyMesh;
  Shader *skyShader;

  GLuint textureId;
  GLuint uniformProjection, uniformView;
};
