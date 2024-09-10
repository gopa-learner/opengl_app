#include "Camera.hpp"
#include "ext/vector_float3.hpp"
#include "geometric.hpp"
#include "glfw3.h"

Camera::Camera(glm::vec3 startposition, glm::vec3 startup, GLfloat startyaw,
               GLfloat startpitch, GLfloat startmovespeed,
               GLfloat startturnspeed) {
  position = startposition;
  worldup = startup;
  yaw = startyaw;
  pitch = startpitch;
  front = glm::vec3(0.0f, 0.0f, -1.0f);
  movemnetspeed = startmovespeed;
  turnspeed = startturnspeed;
  update();
}
void Camera::update() {
  // front
  front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  front.y = sin(glm::radians(pitch));
  front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

  // normalize
  front = glm::normalize(front);

  right = glm::normalize(glm::cross(front, worldup));
  up = glm::normalize(glm::cross(right, front));
}

void Camera ::keycontrol(int key, GLfloat deltaTime) {
  GLfloat velocity = movemnetspeed * deltaTime;

  switch (key) {
  case GLFW_KEY_W:
    position += front * velocity;
    break;

  case GLFW_KEY_S:
    position -= front * velocity;
    break;
  case GLFW_KEY_A:
    position -= right * velocity;
    break;
  case GLFW_KEY_D:
    position += right * velocity;
    break;
  default:
    break;
    // std::cout << "what do you mean by " << key;
  }
}

glm::mat4 Camera::CalculateViewMatrix() {
  return (glm::lookAt(position, position + front, up));
}
Camera::~Camera() {}
void Camera::keycontrol(bool *keys, GLfloat deltaTime) {
  GLfloat velocity = movemnetspeed * deltaTime;

  if (keys[GLFW_KEY_W]) {
    position += front * velocity;
  }

  if (keys[GLFW_KEY_S]) {
    position -= front * velocity;
  }

  if (keys[GLFW_KEY_A]) {
    position -= right * velocity;
  }

  if (keys[GLFW_KEY_D]) {
    position += right * velocity;
  }
}

void Camera::mousecontrol(GLfloat xchange, GLfloat ychange) {
  xchange *= turnspeed;
  ychange *= turnspeed;

  yaw += xchange;
  pitch -= ychange;
  if (pitch > 89.0f) {
    pitch = 89.0f;

  } else if (pitch < -89.0f) {
    pitch = -89.0f;
  }
  update();
}

glm::vec3 Camera::Getcameraposition() { return position; }
glm::vec3 Camera::Getcameradirection() { return glm::normalize(front); }
