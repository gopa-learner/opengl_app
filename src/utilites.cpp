#include "utilities.hpp"
void findAverageNormals(

    unsigned int *indices, unsigned int indicesCount, GLfloat *vertices,
    unsigned int verticeCount, unsigned int vLength, unsigned int normalOffset

) {

  for (size_t i = 0; i < indicesCount; i += 3) {

    uint in0 = indices[i + 0] * vLength;
    uint in1 = indices[i + 1] * vLength;
    uint in2 = indices[i + 2] * vLength;
    glm::vec3 v1 = glm::vec3(vertices[in1] - vertices[in0],
                             vertices[in1 + 1] - vertices[in0 + 1],
                             vertices[in1 + 2] - vertices[in0 + 2]);

    glm::vec3 v2 = glm::vec3(vertices[in2] - vertices[in0],
                             vertices[in2 + 1] - vertices[in0 + 1],
                             vertices[in2 + 2] - vertices[in0 + 2]);
    // the actual normal vector is calculated here
    glm::vec3 normal = glm::normalize(glm::cross(v1, v2));
    /// reusing  in0 in1 in2 for normal offset

    in0 += normalOffset;

    in1 += normalOffset;

    in2 += normalOffset;
    /// setting  vertices

    vertices[in0] += normal.x;
    vertices[in0 + 1] += normal.y;
    vertices[in0 + 2] += normal.z;
    ///
    vertices[in1] += normal.x;
    vertices[in1 + 1] += normal.y;
    vertices[in1 + 2] += normal.z;
    ///
    vertices[in2] += normal.x;
    vertices[in2 + 1] += normal.y;
    vertices[in2 + 2] += normal.z;
  }

  for (size_t i = 0; i < verticeCount / vLength; i++) {

    uint nOffset = i * vLength + normalOffset;
    glm::vec3 vec = glm::vec3(vertices[nOffset], vertices[nOffset + 1],
                              vertices[nOffset + 2]);
    vec = glm::normalize(vec);
    vertices[nOffset] += vec.x;
    vertices[nOffset + 1] += vec.y;
    vertices[nOffset + 2] += vec.z;
  }
}

std::string str_tolower(std::string s) {
  std::transform(s.begin(), s.end(), s.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  return s;
}

bool get_error(GLenum fbuffer) {
  GLenum status = glCheckFramebufferStatus(fbuffer);
  if (status != GL_FRAMEBUFFER_COMPLETE) {

    std::cout << "Frame Buffer Error: |n " << status << "\n";
    return false;
  }
  return true;
}
