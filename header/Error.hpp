#include "GL/glew.h"
#include <iostream>

static void find_error() { std::cout << glewGetErrorString(glGetError()); }
