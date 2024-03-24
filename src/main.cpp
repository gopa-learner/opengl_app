// c++ library

#include <cmath>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
// glew library
#include "GL/glew.h"
// glfw library
#include "GLFW/glfw3.h"
// glm library
#include "Camera.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "ext/vector_float3.hpp"
#include "glm/ext/matrix_clip_space.hpp" // glm::perspective
#include "glm/ext/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale
#include "glm/ext/scalar_constants.hpp" // glm::pi
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/vec3.hpp"   // glm::vec3
#include "glm/vec4.hpp"   // glm::vec4
#include <Window.hpp>
#include <vector>

#include <chrono>

// void inline get_deltatiime() {}

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
GLfloat now = 0.0f;
std::vector<Mesh *> meshlist;

std::vector<Shader *> shaderlist;
Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f,
              0.0f, 5.0f, 0.05f);

// degree  to radians
const float toradians = 3.14159265359 / 180.0f;

// Window dimensions
const GLint WIDTH = 1000, HEIGHT = 900;
// variables to move the tiangle

bool direction = 1;
float trioffset = 0.0f, trimaxoffset = 0.7f, triincrement = 0.00005f;

void createObjects() {

  unsigned int indices[] = {

      // marking points  to render the pyramid
      0, 3, 1, // side of triangle
      //
      1, 3, 2,
      //
      2, 3, 0,
      //
      0, 1, 2

  };

  GLfloat vertices[] = {
      //       |x   | y    |z
      -1.0f, -1.0f, 0.0f, // this is the  left most point
                          //
      0.0f, -1.0f, 1.0f,  // this the  inner most point
                          //
      1.0f, -1.0f, 0.0f,  // this is the right most point
                          //
      0.0f, 1.0f, 0.0f    // tis is the upper most point
  };

  Mesh *obj1 = new Mesh();
  obj1->Create_Mesh(vertices, indices, 12, 12);
  meshlist.push_back(obj1);

  Mesh *obj2 = new Mesh();
  obj2->Create_Mesh(vertices, indices, 12, 12);
  meshlist.push_back(obj2);
}
void CreateShader() {

  Shader *Shader1 = new Shader();

  Shader1->Create_shader();

  shaderlist.push_back(Shader1);
}

int main() {
  GLuint uniformmodel = 0, uniformprojection = 0, uniformview = 0;
  // WINDOW CRAETION

  Window MAINWINDOW(WIDTH, HEIGHT);

  // WINDOW INITIALIZATION
  if (MAINWINDOW.initialize())
    return 0;

  // Get Buffer Size information
  float bufferwidth, bufferheight;

  bufferwidth = MAINWINDOW.getbufferWidth();
  bufferheight = MAINWINDOW.getbufferHeight();

  glm::mat4 projection(1.0f);
  projection = glm::perspective(45.0f, GLfloat(bufferwidth / bufferheight),
                                0.1f, 100.0f);
  createObjects();
  CreateShader();
  uniformprojection = shaderlist[0]->GetProjectionLocation();
  uniformmodel = shaderlist[0]->GetModelLocation();
  uniformview = shaderlist[0]->GetViewLocation();

  float angle = 0;
  // Loop until window closed
  while (!MAINWINDOW.Window_should_close()) {
    // Get + Handle user input events
    now = glfwGetTime();
    deltaTime = now - lastTime;
    lastTime = now;
    glfwPollEvents();
    camera.keycontrol(MAINWINDOW.getkey(), deltaTime);
    camera.mousecontrol(MAINWINDOW.getXchange(), MAINWINDOW.getYchange());
    // Clear window
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderlist[0]->Use_Shader();
    glUniformMatrix4fv(uniformprojection, 1, GL_FALSE,
                       glm::value_ptr(projection));
    glUniformMatrix4fv(uniformview, 1, GL_FALSE,
                       glm::value_ptr(camera.CalculateViewMatrix()));
    glm::mat4 model(1.0f);
    direction ? trioffset += triincrement : trioffset -= triincrement;
    if (abs(trioffset) >= trimaxoffset)
      direction = !direction;

    (angle >= 360) ? angle = 0 : angle += 0.0001;
    model = glm::translate(model, glm::vec3(-0.70f, 0.0f, -2.5f));
    /*   model = glm::rotate(model, angle, glm::vec3(00.0f, 0.0f, 01.0f)); */
    model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
    glUniformMatrix4fv(uniformmodel, 1, GL_FALSE, glm::value_ptr(model));

    meshlist[0]->Render_Mesh();
    model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(0.7f, 0.0f, -2.5f));
    /* model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f)); */
    model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

    glUniformMatrix4fv(uniformmodel, 1, GL_FALSE, glm::value_ptr(model));

    meshlist[1]->Render_Mesh();
    glUseProgram(0);

    MAINWINDOW.Swap_Window_Buffer();
  }

  return 0;
}
