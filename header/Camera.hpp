#pragma once

#include "GL/glew.h"
#include <iostream>

#include "ext/vector_float3.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera {

private:
  glm::vec3 position, front, up, right, worldup;
  GLfloat yaw, pitch, movemnetspeed, turnspeed;
  void update();

public:
  Camera(glm::vec3 startposition, glm::vec3 startup, GLfloat startyaw,
         GLfloat startpitch, GLfloat startmovespeed, GLfloat startturnspeed);
  ~Camera();
  void keycontrol(int key, GLfloat deltaTime);
  void keycontrol(bool *keys, GLfloat deltaTime);
  glm::mat4 CalculateViewMatrix();
  void mousecontrol(GLfloat xchange, GLfloat ychange);
};
