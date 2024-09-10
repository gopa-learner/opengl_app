#include "Window.hpp"
#include "GLFW/glfw3.h"
#include <utility>

void Window::callbacks() {
  glfwSetKeyCallback(MainWindow, handleKeys);
  glfwSetCursorPosCallback(MainWindow, handlemouse);
}

void Window::handleKeys(GLFWwindow *window, int key, int code, int action,
                        int mode) {
  Window *theWindow = static_cast<Window *>(glfwGetWindowUserPointer(window));

  if ((key == GLFW_KEY_ESCAPE) && (action == GLFW_PRESS)) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }

  theWindow->key_nummber = key;
  /*  std::cout << "ok"; */
  if ((key >= 0) && (key < 1024)) {
    if (action == GLFW_PRESS) {
      /*   std::cout << "ok"; */
      theWindow->keys[key] = true;
      theWindow->key_nummber = key;
      /*   std::cout << "pressed key" << key << "\r"; */
    } else if (action == GLFW_RELEASE) {
      theWindow->keys[key] = false;
      theWindow->key_nummber = 0;
      /*  std::cout << "released key " << key << "\r"; */
    }
  }
}

Window::Window(GLint WindowWidth, GLint WindowHeight) {

  Window_HEIGHT = WindowHeight;
  Window_WIDTH = WindowWidth;
}
Window::~Window() {
  glfwDestroyWindow(MainWindow);
  glfwTerminate();
}
GLfloat Window::getbufferHeight() { return buffer_height; }
GLfloat Window::getbufferWidth() { return buffer_width; }
bool Window::Window_should_close() { return glfwWindowShouldClose(MainWindow); }
void Window::Swap_Window_Buffer() { glfwSwapBuffers(MainWindow); }

bool Window::initialize() {

  // Initialise GLFW
  if (!glfwInit()) {
    std::cout << "GLFW initialisation failed!";
    glfwTerminate();
    return 1;
  }
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
  // Setup GLFW window properties
  // OpenGL version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  // Core Profile = No Backwards Compatibility
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // Allow Forward Compatbility
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  // Create the window
  MainWindow =
      glfwCreateWindow(Window_WIDTH, Window_HEIGHT, "Test Window", NULL, NULL);
  if (!MainWindow) {
    std::cout << "GLFW window creation failed!";
    glfwTerminate();
    return 1;
  }
  glfwSetWindowUserPointer(MainWindow, this);
  // Get Buffer Size information

  glfwGetFramebufferSize(MainWindow, &buffer_width, &buffer_height);

  // SETUP CALLBACK FUNCTIONS

  callbacks();

  // SET INPUYT MODE
  /*   glfwSetInputMode(MainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED); */
  // Set context for GLEW to use
  glfwMakeContextCurrent(MainWindow);
  // Allow modern extension features
  glewExperimental = GL_TRUE;

  if (glewInit() != GLEW_OK) {
    std::cout << "GLEW initialisation failed!";
    glfwDestroyWindow(MainWindow);
    glfwTerminate();
    return 1;
  }

  // Setup Viewport size
  glViewport(0, 0, buffer_width, buffer_height);
  glEnable(GL_DEPTH_TEST);
  return 0;
}
void Window::handlemouse(GLFWwindow *window, double Xpos, double Ypos) {

  Window *theWindow = static_cast<Window *>(glfwGetWindowUserPointer(window));

  if (theWindow->mousefirstmoved) {
    theWindow->lastx = Xpos;
    theWindow->lasty = Ypos;
    theWindow->mousefirstmoved = false;
  }

  theWindow->xchange = Xpos - theWindow->lastx;

  theWindow->ychange = Ypos - theWindow->lasty;
  theWindow->lastx = Xpos;
  theWindow->lasty = Ypos;
  // std::cout << "the position of mouse    X:" << theWindow->lastx
  //           << "   Y  :" << theWindow->lasty << "\r";
}
GLfloat Window::getYchange() {
  GLfloat change = 0;
  std::swap(change, ychange);
  return change;
}

GLfloat Window::getXchange() {
  GLfloat change = 0;
  std::swap(change, xchange);
  return change;
}
int Window::getkey() { return key_nummber; }
