#pragma once

#include "Mesh.hpp"
#include "Texture.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <string>
#include <vector>

class Model {
private:
  std::vector<Mesh *> meshlist;
  std::vector<Texture *> texturelist;
  std::vector<unsigned int> meshtotexture;
  void LoadNode(aiNode *node, const aiScene *scene);
  void LoadMesh(aiMesh *mesh, const aiScene *scene);
  void LoadMaterials(const aiScene *scene);

public:
  Model();
  ~Model();
  void LoadModel(const std::string &filename);
  void RenderModel();

  void ClearModel();
};
