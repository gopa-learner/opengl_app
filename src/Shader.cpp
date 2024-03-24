#include "Shader.hpp"
#include <iostream>
#include <string>

Shader::Shader() {

  Shader_ID = 0;
  uniform_Projection = 0;
  uniform_model = 0;
  uniform_view = 0;
}

void Shader::Create_shader(std::string vertexcode_location,
                           std::string fragmetcode_location) {

  Compile_Shader(vertexcode_location.c_str(), fragmetcode_location.c_str());
}

void Shader::Compile_Shader(const char *vertexcode_location,
                            const char *fragmetcode_location) {
  Shader_ID = glCreateProgram();

  if (!Shader_ID)

  {

    std::cout << "error creating shader program \n";
    return;
  }

  // GL_VERTEX_SHADER
  Add_Shader(Shader_ID,
             shaderfile_reader(GL_VERTEX_SHADER, vertexcode_location),
             GL_VERTEX_SHADER);
  // GL_FRAGMENT_SHADER
  Add_Shader(Shader_ID,
             shaderfile_reader(GL_FRAGMENT_SHADER, fragmetcode_location),
             GL_FRAGMENT_SHADER);
  // error handing of shader code
  glLinkProgram(Shader_ID);
  error_checking(Shader_ID, GL_LINK_STATUS);
  glValidateProgram(Shader_ID);
  error_checking(Shader_ID, GL_VALIDATE_STATUS);

  uniform_Projection = glGetUniformLocation(Shader_ID, "projection");
  uniform_model = glGetUniformLocation(Shader_ID, "model");
  uniform_view = glGetUniformLocation(Shader_ID, "view");
}

void Shader::Add_Shader(GLuint pogramid, std::string shadercode,
                        GLenum shadertype) {

  GLuint theshader = glCreateShader(shadertype);
  const char *text = shadercode.c_str();
  int length[1];
  length[0] = shadercode.size();
  glShaderSource(theshader, 1, &text, length);
  glCompileShader(theshader);
  error_checking(theshader, GL_COMPILE_STATUS);
  glAttachShader(pogramid, theshader);
}
//
//  shader  reading
std::string Shader::shaderfile_reader(GLenum type, const char *location) {

  std::ifstream shader_prog;
  if (type == GL_VERTEX_SHADER)
    shader_prog.open(location, std::ios::in);
  else
    shader_prog.open(location, std::ios::in);

  std::string shader_code, temp;
  while (!shader_prog.eof()) {
    std::getline(shader_prog, temp);
    // std::cout << temp;
    shader_code.append(temp + '\n');
  }
  shader_prog.close();
  /*  std::cout << shader_code; */
  return shader_code;
}
void Shader::error_checking(GLuint program, GLenum pname) {

  GLint result = 0;
  GLchar eLog[1024] = {0};

  if (pname != GL_COMPILE_STATUS) {
    glGetProgramiv(program, pname, &result);
    if (!result) {
      glGetProgramInfoLog(program, sizeof(eLog), NULL, eLog);
      std::cout << "error  "
                << ((pname == GL_LINK_STATUS) ? "LINKING " : "VALIDATING")
                << " the program " << eLog << " \n";
      return;
    }
  } else {
    glGetShaderiv(program, pname, &result);
    if (!result)
      std::cout << "error  "
                << "compiling shader "
                << " the program " << eLog << " \n";
    return;
  }
}
void Shader::Use_Shader() { glUseProgram(Shader_ID); }
void Shader::Clear_Shader() {

  (Shader_ID != 0) ? glDeleteProgram(Shader_ID)
                   : void(std::cout << "eror no shader_id found");

  Shader_ID = 0;
  uniform_model = uniform_Projection = 0;
}
Shader::~Shader() { Clear_Shader(); }
//
//       to get the location of the model matrix

GLuint Shader::GetModelLocation() { return uniform_model; }
// to get the projection matrix
//
GLuint Shader::GetProjectionLocation() { return uniform_Projection; }
GLuint Shader::GetViewLocation() { return uniform_view; }
