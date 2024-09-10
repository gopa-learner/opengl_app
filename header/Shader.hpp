
#pragma once
#include "DirectionalLight.hpp"
#include "GL/glew.h"
#include "PointLight.hpp"
#include "Spotlight.hpp"
#include "constants.hpp"
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/types.h>
class Shader {

public:
  Shader();

  void
  Create_shader(std::string vertexcode_location = {"../shader/vertex.vert"},
                std::string fragmetcode_location = {"../shader/fragment.frag"});

  void Create_shader(std::string vertexcode_location,
                     std::string geomcode_location,
                     std::string fragmetcode_location);

  GLuint GetProjectionLocation();
  GLuint GetModelLocation();
  void Use_Shader();
  void Clear_Shader();
  std::string shaderfile_reader(GLenum type, const char *locatiion);
  ~Shader();
  GLuint GetViewLocation();
  GLuint GetAmbientIntensityLocation();
  GLuint GetAmbientcolorLocation();
  GLuint GetDirectionLocation();
  GLuint GetDiffuseIntensityLocaton();
  GLuint GetSpecularIntensityLocation();
  GLuint GetShininessLocation();

  GLuint GeteyepositionLocation();
  GLuint GetOmniLightposLocation() { return uniform_OmniLightPos; }
  GLuint GetFarPlaneLocation() { return uniform_farplane; }
  void setDirectionalLight(DirectionalLight *dlight);
  void setPointLight(PointLight *Plightlist, uint pointLight_count,
                     uint textureunit, uint offset);
  void setSpotLight(Spotlight *slightlist, uint Spotlight_count,
                    uint textureunit, uint offset);
  void setDirectionalLightTransform(glm::mat4 *transform);
  void setDirectionalLightShadowmap(GLuint textureunit);
  void setTexture(GLenum texture);
  void setOmniLightatrices(std::array<glm::mat4, 6> transform);
  void error_checking(GLuint, GLenum);

  void error_checking(GLenum);

private:
  GLuint Shader_ID, uniform_Projection, uniform_model, uniform_view,
      uniform_specularIntensity, uniform_shininess, uniform_eyeposition,
      uniform_PointLight_count, uniform_SpotLight_count,
      Uniform_DirectionalLightTransform, uniform_DirectionShadowMap,
      uniform_texture, uniform_DirectionShadowTransform, uniform_OmniLightPos,
      uniform_farplane;

  std::array<GLuint, 6> uniformLightMatrices;

  // DIRECTIONAL LIGHT
  struct {
    GLuint uniform_AmbientIntensity, uniform_AmbientColor, uniform_Direction,
        uniform_DiffuseIntensity;

  } Uniform_DirectionalLight;
  // POINT LIGHT

  struct {
    GLuint uniform_AmbientIntensity, uniform_DiffuseIntensity,
        uniform_AmbientColor, uniform_position, uniform_exponential,
        uniform_linear, uniform_constant, uniform_nearplane, uniform_farplane;

  } Uniform_PointLight[MAX_POINT_LIGHT];
  // SPOT LIGHT
  struct {
    GLuint uniform_AmbientIntensity, uniform_DiffuseIntensity,
        uniform_AmbientColor, uniform_position, uniform_exponential,
        uniform_linear, uniform_constant, uniform_direction, uniform_edge;
  } Uniform_SpotLight[MAX_SPOT_LIGHT];
  struct {
    GLuint shadowmap;
    GLuint farplane;

  } Uniform_OmniShadowMap[MAX_POINT_LIGHT + MAX_SPOT_LIGHT];
  void Compile_Shader(const char *vertexCode_location,
                      const char *geomcode_location,
                      const char *fragmetcode_location);
  void Add_Shader(GLuint pogramid, std::string shadercode, GLenum shadertype);
};
