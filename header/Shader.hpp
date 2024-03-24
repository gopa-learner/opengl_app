#pragma once
#include <fstream>
#include <iostream>
#include <string>

#include "GL/glew.h"
class Shader {

public:
  Shader();

  void
  Create_shader(std::string vertexcode_location = {"../shader/vertex.vert"},
                std::string fragmetcode_location = {"../shader/fragment.frag"});
  GLuint GetProjectionLocation();
  GLuint GetModelLocation();
  void Use_Shader();
  void Clear_Shader();
  std::string shaderfile_reader(GLenum type, const char *locatiion);
  ~Shader();
  GLuint GetViewLocation();

private:
  GLuint Shader_ID, uniform_Projection, uniform_model, uniform_view;

  void error_checking(GLuint, GLenum);
  void Compile_Shader(const char *vertexCode_location,
                      const char *fragmetcode_location);
  void Add_Shader(GLuint pogramid, std::string shadercode, GLenum shadertype);
};
