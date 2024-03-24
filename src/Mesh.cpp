#include "Mesh.hpp"

Mesh::Mesh() {

  VAO = 0;
  VBO = 0;
  IBO = 0;
  indexcount = 0;
}
void Mesh::Create_Mesh(GLfloat *vertices, unsigned int *indices,
                       unsigned int number_of_vertices,
                       unsigned int number_of_indices) {
  indexcount = number_of_vertices;
  // array generation
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  glGenBuffers(1, &IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * number_of_indices,
               indices, GL_STATIC_DRAW);

  glGenBuffers(1, &VBO);
  // binding buffer
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * number_of_vertices,
               vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  // removing buffer

  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void Mesh::Render_Mesh() {
  glBindVertexArray(VAO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
  glDrawElements(GL_TRIANGLES, indexcount, GL_UNSIGNED_INT, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void Mesh::Clear_Mesh() {
  (IBO != 0) ? glDeleteBuffers(1, &IBO) : void(std::cout << "no IBO found");
  (VBO != 0) ? glDeleteBuffers(1, &VBO) : void(std::cout << "no VBO found");
  (VAO != 0) ? glDeleteVertexArrays(1, &VAO)
             : void(std::cout << "no VAO found");

  VAO = VBO = IBO = 0;
  indexcount = 0;
}
Mesh::~Mesh() { Clear_Mesh(); }
