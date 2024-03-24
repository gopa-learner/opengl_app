#pragma once
#include "GL/glew.h"
#include <iostream>
class Mesh {

public:
  Mesh();
  void Create_Mesh(GLfloat *vertices, unsigned int *indices,
                   unsigned int number_of_vertices,
                   unsigned int number_of_indices);
  void Render_Mesh();
  void Clear_Mesh();
  ~Mesh();

private:
  GLuint VAO, VBO, IBO;
  GLsizei indexcount;
};
