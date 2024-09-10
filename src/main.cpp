// c++ library
#include "Material.hpp"
#include "OmniShadowmap.hpp"
#include "Spotlight.hpp"
#include "constants.hpp"
#include "ext/quaternion_transform.hpp"
#include "fwd.hpp"
#include "trigonometric.hpp"
#include <cstddef>
#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#define STB_IMAGE_IMPLEMENTATION
// glew library
#include "GL/glew.h"
// glfw library
#include "GLFW/glfw3.h"
// glm library
#include "Camera.hpp"
#include "DirectionalLight.hpp"
#include "Mesh.hpp"
#include "Model.hpp"
#include "PointLight.hpp"
#include "Shader.hpp"
#include "Skybox.hpp"
#include "Spotlight.hpp"
#include "Texture.hpp"
#include "Window.hpp"
#include "assimp/Importer.hpp"
#include "common.hpp"
#include "ext/vector_float3.hpp"
#include "glm/ext/matrix_clip_space.hpp" // glm::perspective
#include "glm/ext/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale
#include "glm/gtc/type_ptr.hpp"
#include "utilities.hpp"
#include <vector>
// void inline get_deltatiime() {}
GLuint uniformmodel = 0, uniformprojection = 0, uniformview = 0,
       uniformEyeposition = 0, uniformOmnilightpos = 0, uniformfarplane = 0;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
GLfloat now = 0.0f;
std::vector<Mesh *> meshlist;
Shader directionalshader, OmniShadowshader;

std::vector<Shader *> shaderlist;
Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f,
              0.0f, 5.0f, 0.5f);
Texture brick_texture("../texture/brick.png");

Texture dirt_texture("../texture/dirt.png");
Texture plain_texture("../texture/plain.png");
// degree  to radians
const float toradians = 3.14159265359 / 180.0f;

PointLight Pointlights[MAX_POINT_LIGHT];
Spotlight Spotlights[MAX_SPOT_LIGHT];
// Window dimensions
const GLint WIDTH = 1366, HEIGHT = 768;
// variables to move the tiangle
Material shiny(256, 5.0f), dull(4, 0.3f);
Model xwing, boombox, katana, boulder, cannon, plant;
glm::mat4 projection(1.0f);

// creating  lighting1;
Skybox skybox;
DirectionalLight mainLight;

uint PointLightcount = 0, spotlightcount = 0;

void createObjects() {

  unsigned int indices[] = {

      // marking points  to render the pyramid
      0, 3, 1, // side of triangle
      //
      1, 3, 2,
      //
      2, 3, 0,
      //
      0, 1, 2

  };

  GLfloat vertices[] = {//	x      y      z			u	  v
                        // nx	  ny    nz
                        -1.0f, -1.0f, -0.6f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                        0.0f,  -1.0f, 1.0f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
                        1.0f,  -1.0f, -0.6f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                        0.0f,  1.0f,  0.0f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f};

  unsigned int floorIndices[] = {0, 2, 1, 1, 2, 3};

  GLfloat floorVertices[] = {-10.0f, 0.0f,  -10.0f, 0.0f,   0.0f,  0.0f,  -1.0f,
                             0.0f,   10.0f, 0.0f,   -10.0f, 10.0f, 0.0f,  0.0f,
                             -1.0f,  0.0f,  -10.0f, 0.0f,   10.0f, 0.0f,  10.0f,
                             0.0f,   -1.0f, 0.0f,   10.0f,  0.0f,  10.0f, 10.0f,
                             10.0f,  0.0f,  -1.0f,  0.0f};

  // find he normal of vertices
  findAverageNormals(indices, 12, vertices, 32, 8, 5);
  Mesh *obj1 = new Mesh();
  obj1->Create_Mesh(vertices, indices, 32, 12);
  meshlist.push_back(obj1);

  Mesh *obj2 = new Mesh();
  obj2->Create_Mesh(vertices, indices, 32, 12);

  meshlist.push_back(obj2);

  Mesh *obj3 = new Mesh();
  obj3->Create_Mesh(floorVertices, floorIndices, 32, 6);
  meshlist.push_back(obj3);
}
void CreateShader() {

  Shader *Shader1 = new Shader();

  Shader1->Create_shader();

  shaderlist.push_back(Shader1);

  directionalshader.Create_shader("../shader/directional_shadowmap.vert",
                                  "../shader/directional_shadowmap.frag");

  OmniShadowshader.Create_shader("../shader/omnishadowmap.vert",
                                 "../shader/omnishadowmap.geom",
                                 "../shader/omnishadowmap.frag");
}
float angle = 0;
void render() {

  // object 1
  glm::mat4 model(1.0f);

  model = glm::translate(model, glm::vec3(0.0f, -2.0f, 2.5f));
  glUniformMatrix4fv(uniformmodel, 1, GL_FALSE, glm::value_ptr(model));
  dull.useMaterial(shaderlist[0]->GetSpecularIntensityLocation(),
                   shaderlist[0]->GetShininessLocation());
  brick_texture.Use_tetxtue();

  meshlist[0]->Render_Mesh();
  // object2
  model = glm::mat4(1.0f);

  model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));

  dull.useMaterial(shaderlist[0]->GetSpecularIntensityLocation(),
                   shaderlist[0]->GetShininessLocation());
  glUniformMatrix4fv(uniformmodel, 1, GL_FALSE, glm::value_ptr(model));
  dirt_texture.Use_tetxtue();

  meshlist[1]->Render_Mesh();

  /*  object3 */

  model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(0.0f, -4.0f, 2.5f));

  shiny.useMaterial(shaderlist[0]->GetSpecularIntensityLocation(),
                    shaderlist[0]->GetShininessLocation());
  glUniformMatrix4fv(uniformmodel, 1, GL_FALSE, glm::value_ptr(model));
  plain_texture.Use_tetxtue();

  meshlist[2]->Render_Mesh();

  /* xwing */

  model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(-5.0f, 0.0f, 10.0f));
  model = glm::scale(model, glm::vec3(0.006, 0.006, 0.006));

  model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
  angle += 0.01;
  angle = std::fmod(angle, 360);

  model = glm::rotate(model, angle * toradians, glm::vec3(0.0f, -3.0f, 0.0f));
  shiny.useMaterial(shaderlist[0]->GetSpecularIntensityLocation(),
                    shaderlist[0]->GetShininessLocation());
  glUniformMatrix4fv(uniformmodel, 1, GL_FALSE, glm::value_ptr(model));

  xwing.RenderModel();

  // model = glm::mat4(1.0f);
  // model = glm::translate(model, glm::vec3(-3.0f, -5.0f, 0.0f));
  // model = glm::scale(model, glm::vec3(5));
  // shiny.useMaterial(shaderlist[0]->GetSpecularIntensityLocation(),
  //                   shaderlist[0]->GetShininessLocation());
  // glUniformMatrix4fv(uniformmodel, 1, GL_FALSE, glm::value_ptr(model));
  // boombox.RenderModel();
  //
  // model = glm::mat4(1.0f);
  // model = glm::translate(model, glm::vec3(-3.0f, -4.0f, 5.0f));
  // model = glm::scale(model, glm::vec3(5));
  // shiny.useMaterial(shaderlist[0]->GetSpecularIntensityLocation(),
  //                   shaderlist[0]->GetShininessLocation());
  // glUniformMatrix4fv(uniformmodel, 1, GL_FALSE, glm::value_ptr(model));
  // boulder.RenderModel();
  //
  // model = glm::mat4(1.0f);
  // model = glm::translate(model, glm::vec3(3.0f, -1.0f, 0.0f));
  // model = glm::scale(model, glm::vec3(5));
  // // model = glm::rotate(model, 90, glm::vec3(0.0f, 0.0f, 1.0f));
  // //
  // model = glm::rotate(model, 180 * toradians, glm::vec3(0.0f, 0.0f, 1.0f));
  // shiny.useMaterial(shaderlist[0]->GetSpecularIntensityLocation(),
  //                   shaderlist[0]->GetShininessLocation());
  // glUniformMatrix4fv(uniformmodel, 1, GL_FALSE, glm::value_ptr(model));
  // cannon.RenderModel();
  //
  // model = glm::mat4(1.0f);
  // model = glm::translate(model, glm::vec3(3.0f, 3.0f, 3.0f));
  // model = glm::scale(model, glm::vec3(5));
  // shiny.useMaterial(shaderlist[0]->GetSpecularIntensityLocation(),
  //                   shaderlist[0]->GetShininessLocation());
  // glUniformMatrix4fv(uniformmodel, 1, GL_FALSE, glm::value_ptr(model));
  // katana.RenderModel();
  // model = glm::mat4(1.0f);
  // model = glm::translate(model, glm::vec3(-3.0f, -4.0f, 0.0f));
  // model = glm::scale(model, glm::vec3(5));
  // shiny.useMaterial(shaderlist[0]->GetSpecularIntensityLocation(),
  //                   shaderlist[0]->GetShininessLocation());
  // glUniformMatrix4fv(uniformmodel, 1, GL_FALSE, glm::value_ptr(model));
  // plant.RenderModel();
}

glm::vec3 positionofpointlight = glm::vec3(-4.0f, 2.0f, -1.0f);
void RenderPass(glm::mat4 viewMatrix, glm::mat4 projectionmatrix) {
  glViewport(0, 0, WIDTH, HEIGHT);

  // Clear window
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  skybox.DrawSkybox(viewMatrix, projectionmatrix);

  shaderlist[0]->Use_Shader();
  glm::vec3 campos = glm::vec3(0.0f);
  // geting uniforn location for the following
  uniformprojection = shaderlist[0]->GetProjectionLocation();
  uniformmodel = shaderlist[0]->GetModelLocation();
  uniformview = shaderlist[0]->GetViewLocation();
  uniformEyeposition = shaderlist[0]->GeteyepositionLocation();

  // setting campos

  glUniformMatrix4fv(uniformprojection, 1, GL_FALSE,
                     glm::value_ptr(projectionmatrix));
  glUniformMatrix4fv(uniformview, 1, GL_FALSE, glm::value_ptr(viewMatrix));
  campos = camera.Getcameraposition();
  glUniform3f(uniformEyeposition, campos.x, campos.y, campos.z);

  // setting lighting options
  glm::vec3 pos = campos;
  pos -= glm::vec3(0, 0.2f, 0);

  Spotlights[0].flashlight(pos, camera.Getcameradirection());
  glm::mat4 rotaionmat = glm::mat4(1.0f);
  rotaionmat = glm::rotate(rotaionmat, angle, glm::vec3(0.0f, 0.0f, 1.0f));
  positionofpointlight =
      glm::vec3(rotaionmat * glm::vec4(positionofpointlight, 1.0f));
  // Pointlights[0].setposition(positionofpointlight);
  shaderlist[0]->setDirectionalLight(&mainLight);
  shaderlist[0]->setPointLight(Pointlights, PointLightcount, 3, 0);
  shaderlist[0]->setSpotLight(Spotlights, spotlightcount, 3 + PointLightcount,
                              PointLightcount);

  glm::mat4 temporary = mainLight.calculateLightTransform();

  shaderlist[0]->setDirectionalLightTransform(&temporary);

  ::mainLight.getShadowmap()->Read(GL_TEXTURE2);
  shaderlist[0]->setTexture(1);
  shaderlist[0]->setDirectionalLightShadowmap(2);
  shaderlist[0]->error_checking(GL_VALIDATE_STATUS);
  render();
}
void DirectionalShadowmap(DirectionalLight *dlight) {
  directionalshader.Use_Shader();
  glViewport(0, 0, dlight->getShadowmap()->Get_shadowWidth(),

             dlight->getShadowmap()->Get_shadowHeight());

  dlight->getShadowmap()->Write();

  glClear(GL_DEPTH_BUFFER_BIT);

  uniformmodel = directionalshader.GetModelLocation();

  glm::mat4 temp = dlight->calculateLightTransform();

  directionalshader.setDirectionalLightTransform(&temp);

  directionalshader.error_checking(GL_VALIDATE_STATUS);

  render();
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OmniShadowMapPass(PointLight *plight) {
  glViewport(0, 0, plight->getShadowmap()->Get_shadowWidth(),

             plight->getShadowmap()->Get_shadowHeight());

  OmniShadowshader.Use_Shader();

  uniformmodel = OmniShadowshader.GetModelLocation();
  uniformOmnilightpos = OmniShadowshader.GetOmniLightposLocation();
  uniformfarplane = OmniShadowshader.GetFarPlaneLocation();

  plight->getShadowmap()->Write();

  glClear(GL_DEPTH_BUFFER_BIT);

  glUniform3f(uniformOmnilightpos, plight->getPosition().x,
              plight->getPosition().y, plight->getPosition().z);
  glUniform1f(uniformfarplane, plight->getfarplane());

  auto temp = plight->calculateLightTransform();

  OmniShadowshader.setOmniLightatrices(temp);

  OmniShadowshader.error_checking(GL_VALIDATE_STATUS);
  render();
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
int main() {

  // WINDOW CRAETION

  Window MAINWINDOW(WIDTH, HEIGHT);

  // WINDOW INITIALIZATION
  if (MAINWINDOW.initialize())
    return 0;

  // Get Buffer Size information
  float bufferwidth, bufferheight;

  bufferwidth = MAINWINDOW.getbufferWidth();
  bufferheight = MAINWINDOW.getbufferHeight();
  // projection matrix INITIALIZATION and creation
  projection =
      glm::perspective(glm::radians(45.0f), GLfloat(bufferwidth / bufferheight),

                       0.1f, 100.0f);
  // object creation  in function
  createObjects();

  // shader creation in the functtion
  CreateShader();
  mainLight = DirectionalLight(2048, 2048, glm ::vec3(0.0f), 0.3f,
                               glm::vec3(0.0f, -3.0f, -1.0f), 0.2f);

  Pointlights[0] =
      PointLight(2048, 2048, glm::vec3(0.0f, 1.0f, 1.0f), 1.0f, 2.0f,
                 glm::vec3(0.3f, 0.02f, 0.01f), glm::vec3(2.0f), 0.01f, 100.0f);

  PointLightcount += 1;
  Pointlights[1] = PointLight(2048, 2048, glm::vec3(1.0f, 1.0f, 0.0f), 01.0f,
                              3.0f, glm::vec3(0.3f, 0.2f, 0.1f),
                              glm::vec3(-2.0f, 03.0f, 0.0f), 0.1f, 100.0f);

  PointLightcount += 1;
  Spotlights[0] =
      Spotlight(2048, 2048, glm::vec3(1.0f, 0.50f, 01.0f), 0.30f, 0.50f,
                glm::vec3(0.01f, 0.02f, 0.70f), glm::vec3(2, 2, 0), 25.0f,
                glm::vec3(0.0f, -1.0f, 0.0f), 0.1f, 100.0f);
  spotlightcount++;

  std::vector<std::string> skyboxFaces;
  skyboxFaces.push_back("../texture/Skybox/cupertin-lake_rt.tga");
  skyboxFaces.push_back("../texture/Skybox/cupertin-lake_lf.tga");
  skyboxFaces.push_back("../texture/Skybox/cupertin-lake_up.tga");
  skyboxFaces.push_back("../texture/Skybox/cupertin-lake_dn.tga");
  skyboxFaces.push_back("../texture/Skybox/cupertin-lake_bk.tga");
  skyboxFaces.push_back("../texture/Skybox/cupertin-lake_ft.tga");

  skybox = Skybox(skyboxFaces);

  xwing.LoadModel("../MODEL/x-wing.obj");
  // boombox.LoadModel("../MODEL/boombox_4k.gltf/boombox_4k.gltf");
  // katana.LoadModel(
  //     "../MODEL/antique_katana_01_8k.gltf/antique_katana_01_8k.gltf");
  // boulder.LoadModel("../MODEL/boulder_01_8k.gltf/boulder_01_8k.gltf");
  // cannon.LoadModel("../MODEL/cannon_01_8k.gltf/cannon_01_8k.gltf");
  // plant.LoadModel("../MODEL/potted_plant_04_8k.gltf/potted_plant_04_8k.gltf");

  // loading texture to cpu memory
  brick_texture.Load_textureA();
  plain_texture.Load_textureA();
  dirt_texture.Load_textureA();
  // brick_texture.Load_texture();
  // creating light works
  // Loop until window closed
  while (!MAINWINDOW.Window_should_close()) {
    // Get + Handle user input events
    now = glfwGetTime();
    deltaTime = now - lastTime;
    lastTime = now;
    // glfwWaitEvents();
    glfwPollEvents();
    camera.keycontrol(MAINWINDOW.getkey(), deltaTime);
    camera.mousecontrol(MAINWINDOW.getXchange(), MAINWINDOW.getYchange());
    DirectionalShadowmap(&mainLight);

    for (auto i = 0; i < PointLightcount; i++)
      OmniShadowMapPass(&Pointlights[i]);
    for (auto i = 0; i < spotlightcount; i++)
      OmniShadowMapPass(&Spotlights[i]);
    RenderPass(camera.CalculateViewMatrix(), projection);
    MAINWINDOW.Swap_Window_Buffer();
  }

  return 0;
}
