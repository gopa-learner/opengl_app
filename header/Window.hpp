
#pragma once
#include "GL/glew.h"
//
#include "GL/gl.h"
#include "GLFW/glfw3.h"
#include <iostream>

class Window {

public:
  Window(GLint WindowWidth = 800, GLint WindowHeight = 600);
  ~Window();
  GLfloat getbufferWidth();
  GLfloat getbufferHeight();
  bool Window_should_close();
  void Swap_Window_Buffer();
  bool *getkeys() { return keys; }
  int getkey();
  GLfloat getXchange();
  GLfloat getYchange();
  bool initialize();

private:
  GLint Window_WIDTH, Window_HEIGHT, buffer_width, buffer_height;
  GLfloat lastx = 0.0f, lasty = 0.0f, xchange = 0.0f, ychange = 0.0f;
  bool keys[1024] = {0}, mousefirstmoved;
  int key_nummber = 0;

  GLFWwindow *MainWindow;
  void callbacks();
  static void handleKeys(GLFWwindow *window, int key, int code, int action,
                         int mode);
  static void handlemouse(GLFWwindow *window, double Xpos, double Ypos);
};
