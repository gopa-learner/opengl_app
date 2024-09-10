#pragma once
#include "GL/glew.h"
#include "ext/quaternion_geometric.hpp"
#include "ext/vector_float3.hpp"
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
#include <sys/types.h>

#include <cctype>

void findAverageNormals(

    unsigned int *indices, unsigned int indicesCount, GLfloat *vertices,
    unsigned int verticeCount, unsigned int vLength, unsigned int normalOffset

);
std::string str_tolower(std::string s);

bool get_error(GLenum fbuffer);
