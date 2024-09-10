#include "Shader.hpp"
#include "Light.hpp"
#include "Material.hpp"
#include "PointLight.hpp"
#include "constants.hpp"
#include "gtc/type_ptr.hpp"
#include <cstddef>
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

  Compile_Shader(vertexcode_location.c_str(), NULL,
                 fragmetcode_location.c_str());
}
void Shader::Create_shader(std::string vertexcode_location,
                           std::string geomcode_loaction,
                           std::string fragmetcode_location) {

  Compile_Shader(vertexcode_location.c_str(), geomcode_loaction.c_str(),
                 fragmetcode_location.c_str());
}

void Shader::Compile_Shader(const char *vertexcode_location,
                            const char *geomcode_loaction,
                            const char *fragmetcode_location) {
  Shader_ID = glCreateProgram();
  // error_checking(Shader_ID, GL_VALIDATE_STATUS);
  if (!Shader_ID)

  {

    std::cout << "error creating shader program \n";
    return;
  }

  // GL_VERTEX_SHADER
  //
  //
  std::cout << "adding shader" << vertexcode_location << "\n";
  Add_Shader(Shader_ID,
             shaderfile_reader(GL_VERTEX_SHADER, vertexcode_location),
             GL_VERTEX_SHADER);
  if (geomcode_loaction != NULL) {

    std::cout << "adding shader" << geomcode_loaction << "\n";

    // GL_geomerty_SHADER
    Add_Shader(Shader_ID,
               shaderfile_reader(GL_GEOMETRY_SHADER, geomcode_loaction),
               GL_GEOMETRY_SHADER);
  }

  // GL_FRAGMENT_SHADER
  //
  //

  std::cout << "adding shader" << fragmetcode_location << "\n";
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
  Uniform_DirectionalLight.uniform_AmbientColor =
      glGetUniformLocation(Shader_ID, "directionalLight.base.color");
  Uniform_DirectionalLight.uniform_AmbientIntensity =
      glGetUniformLocation(Shader_ID, "directionalLight.base.ambientIntensity");

  Uniform_DirectionalLight.uniform_DiffuseIntensity =
      glGetUniformLocation(Shader_ID, "directionalLight.base.diffuseIntensity");
  Uniform_DirectionalLight.uniform_Direction =
      glGetUniformLocation(Shader_ID, "directionalLight.direction");
  uniform_shininess = glGetUniformLocation(Shader_ID, "material.shininess");
  uniform_specularIntensity =
      glGetUniformLocation(Shader_ID, "material.specular_intensity");
  uniform_eyeposition = glGetUniformLocation(Shader_ID, "eyeposition");
  // point light uniform collection
  uniform_PointLight_count = glGetUniformLocation(Shader_ID, "PointlightCount");

  for (int i = 0; i < MAX_POINT_LIGHT; i++) {
    std::string PointLightcall = "Pointlights[]";

    PointLightcall.insert(12, std::to_string(i));
    std::string color = PointLightcall + ".base.color",
                aintensity = PointLightcall + ".base.ambientIntensity",
                dintensity = PointLightcall + ".base.diffuseIntensity",
                position = PointLightcall + ".position",
                constant = PointLightcall + ".constant",
                linear = PointLightcall + ".Linear",
                exponent = PointLightcall + ".exponent";

    Uniform_PointLight[i].uniform_AmbientIntensity =
        glGetUniformLocation(Shader_ID, aintensity.c_str());

    Uniform_PointLight[i].uniform_DiffuseIntensity =
        glGetUniformLocation(Shader_ID, dintensity.c_str());

    Uniform_PointLight[i].uniform_AmbientColor =
        glGetUniformLocation(Shader_ID, color.c_str());

    Uniform_PointLight[i].uniform_position =
        glGetUniformLocation(Shader_ID, position.c_str());

    Uniform_PointLight[i].uniform_exponential =
        glGetUniformLocation(Shader_ID, exponent.c_str());

    Uniform_PointLight[i].uniform_linear =
        glGetUniformLocation(Shader_ID, linear.c_str());

    Uniform_PointLight[i].uniform_constant =
        glGetUniformLocation(Shader_ID, constant.c_str());
  }

  uniform_SpotLight_count = glGetUniformLocation(Shader_ID, "SpotlightCount");

  for (int i = 0; i < MAX_SPOT_LIGHT; i++) {
    std::string SpotLightcall = "Spotlights[]";

    SpotLightcall.insert(11, std::to_string(i));
    std::string color = SpotLightcall + ".base.base.color",
                aintensity = SpotLightcall + ".base.base.ambientIntensity",
                dintensity = SpotLightcall + ".base.base.diffuseIntensity",
                position = SpotLightcall + ".base.position",
                constant = SpotLightcall + ".base.constant",
                linear = SpotLightcall + ".base.Linear",
                exponent = SpotLightcall + ".base.exponent",
                direction = SpotLightcall + ".direction",
                edge = SpotLightcall + ".edge";

    // std::cout << color << aintensity << dintensity << position << constant
    //           << linear << exponent << direction << edge << "\n";
    Uniform_SpotLight[i].uniform_AmbientIntensity =
        glGetUniformLocation(Shader_ID, aintensity.c_str());

    Uniform_SpotLight[i].uniform_DiffuseIntensity =
        glGetUniformLocation(Shader_ID, dintensity.c_str());

    Uniform_SpotLight[i].uniform_AmbientColor =
        glGetUniformLocation(Shader_ID, color.c_str());

    Uniform_SpotLight[i].uniform_position =
        glGetUniformLocation(Shader_ID, position.c_str());

    Uniform_SpotLight[i].uniform_exponential =
        glGetUniformLocation(Shader_ID, exponent.c_str());

    Uniform_SpotLight[i].uniform_linear =
        glGetUniformLocation(Shader_ID, linear.c_str());

    Uniform_SpotLight[i].uniform_constant =
        glGetUniformLocation(Shader_ID, constant.c_str());

    Uniform_SpotLight[i].uniform_direction =
        glGetUniformLocation(Shader_ID, direction.c_str());
    Uniform_SpotLight[i].uniform_edge =
        glGetUniformLocation(Shader_ID, edge.c_str());
  }

  uniform_texture = glGetUniformLocation(Shader_ID, "theTexture");
  uniform_DirectionShadowTransform =
      glGetUniformLocation(Shader_ID, "DirectionalLightTransform");

  uniform_DirectionShadowMap =
      glGetUniformLocation(Shader_ID, "theDirectionalShadowMap");

  for (size_t i = 0; i < 6; i++) {

    std::string shadowmap = "lightMatrices[]";
    shadowmap.insert(14, std::to_string(i));
    uniformLightMatrices[i] =
        glGetUniformLocation(Shader_ID, shadowmap.c_str());
  }

  uniform_OmniLightPos = glGetUniformLocation(Shader_ID, "lightPos");
  uniform_farplane = glGetUniformLocation(Shader_ID, "farPlane");

  for (size_t i = 0; i < (MAX_SPOT_LIGHT + MAX_POINT_LIGHT); i++) {

    std::string shadowmap = "omnishadowmaps[]";
    shadowmap.insert(15, std::to_string(i));
    std::string shadow = shadowmap + ".shadowmap";
    std::string fardistance = shadowmap + ".farplane";
    Uniform_OmniShadowMap[i].shadowmap =
        glGetUniformLocation(Shader_ID, shadow.c_str());
    Uniform_OmniShadowMap[i].farplane =
        glGetUniformLocation(Shader_ID, fardistance.c_str());
  }
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
      std::cout << "error  compiling shader " << " the program " << eLog
                << " \n";
    return;
  }
}

void Shader::error_checking(GLenum pname) {
  GLuint program = this->Shader_ID;
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
      std::cout << "error  compiling shader " << " the program " << eLog
                << " \n";
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
GLuint Shader::GetAmbientIntensityLocation() {
  return Uniform_DirectionalLight.uniform_AmbientIntensity;
}
GLuint Shader::GetAmbientcolorLocation() {
  return Uniform_DirectionalLight.uniform_AmbientColor;
}
GLuint Shader::GetDirectionLocation() {
  return Uniform_DirectionalLight.uniform_Direction;
}
GLuint Shader::GetDiffuseIntensityLocaton() {
  return Uniform_DirectionalLight.uniform_DiffuseIntensity;
}
GLuint Shader::GetSpecularIntensityLocation() {
  return uniform_specularIntensity;
}
GLuint Shader::GetShininessLocation() { return uniform_shininess; }

GLuint Shader::GeteyepositionLocation() { return uniform_eyeposition; }

void Shader::setDirectionalLight(DirectionalLight *dlight) {

  dlight->useDirectionalLight(Uniform_DirectionalLight.uniform_AmbientIntensity,
                              Uniform_DirectionalLight.uniform_AmbientColor,
                              Uniform_DirectionalLight.uniform_DiffuseIntensity,
                              Uniform_DirectionalLight.uniform_Direction);
}

void Shader::setPointLight(PointLight *plightList, uint pointLightcount,
                           uint textureunit, uint offset) {
  if (pointLightcount > MAX_POINT_LIGHT)
    pointLightcount = MAX_POINT_LIGHT;
  glUniform1i(uniform_PointLight_count, pointLightcount);

  for (int i = 0; i < pointLightcount; i++)

  {
    // std::cout << i << "\n";
    plightList[i].UsePointLight(Uniform_PointLight[i].uniform_AmbientIntensity,
                                Uniform_PointLight[i].uniform_AmbientColor,
                                Uniform_PointLight[i].uniform_DiffuseIntensity,
                                Uniform_PointLight[i].uniform_position,
                                Uniform_PointLight[i].uniform_exponential,
                                Uniform_PointLight[i].uniform_linear,
                                Uniform_PointLight[i].uniform_constant);

    plightList[i].getShadowmap()->Read(GL_TEXTURE0 + textureunit + i);
    glUniform1i(Uniform_OmniShadowMap[i + offset].shadowmap, textureunit + i);
    glUniform1f(Uniform_OmniShadowMap[i + offset].farplane,
                plightList[i].getfarplane());
  }
}

void Shader::setSpotLight(Spotlight *slightlist, uint Spotlight_count,
                          uint textureunit, uint offset) {
  if (Spotlight_count > MAX_POINT_LIGHT)
    Spotlight_count = MAX_POINT_LIGHT;
  glUniform1i(uniform_SpotLight_count, Spotlight_count);

  for (int i = 0; i < Spotlight_count; i++)

  {
    // std::cout << i << "\n";
    slightlist[i].UseSpotLight(Uniform_SpotLight[i].uniform_AmbientIntensity,
                               Uniform_SpotLight[i].uniform_AmbientColor,
                               Uniform_SpotLight[i].uniform_DiffuseIntensity,
                               Uniform_SpotLight[i].uniform_position,
                               Uniform_SpotLight[i].uniform_exponential,
                               Uniform_SpotLight[i].uniform_linear,
                               Uniform_SpotLight[i].uniform_constant,
                               Uniform_SpotLight[i].uniform_direction,
                               Uniform_SpotLight[i].uniform_edge);

    slightlist[i].getShadowmap()->Read(GL_TEXTURE0 + textureunit + i);
    glUniform1i(Uniform_OmniShadowMap[i + offset].shadowmap, textureunit + i);
    glUniform1f(Uniform_OmniShadowMap[i + offset].farplane,
                slightlist[i].getfarplane());
  }
}
void Shader::setTexture(GLuint textureunit) {

  glUniform1i(uniform_texture, textureunit);
}

void Shader::setDirectionalLightShadowmap(GLuint textureunit) {

  glUniform1i(uniform_DirectionShadowMap, textureunit);
}

void Shader::setDirectionalLightTransform(glm::mat4 *transform) {

  glUniformMatrix4fv(uniform_DirectionShadowTransform, 1, GL_FALSE,
                     glm::value_ptr(*transform));
}

void Shader::setOmniLightatrices(std::array<glm::mat4, 6> transform) {

  for (int i = 0; i < 6; i++) {

    glUniformMatrix4fv(uniformLightMatrices[i], 1, GL_FALSE,
                       glm::value_ptr(transform[i]));
  }
}
