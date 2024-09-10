#include "Model.hpp"
#include "utilities.hpp"
#include <iostream>
Model::Model() {}

void Model::RenderModel() {
  for (size_t i = 0; i < meshlist.size(); i++) {
    unsigned int materialIndex = meshtotexture[i];

    if (materialIndex < texturelist.size() && texturelist[materialIndex]) {
      texturelist[materialIndex]->Use_tetxtue();
    }

    meshlist[i]->Render_Mesh();
  }
}

void Model::LoadModel(const std::string &filename) {
  Assimp::Importer importer;
  const aiScene *scene =
      importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs |
                                      aiProcess_GenSmoothNormals |
                                      aiProcess_JoinIdenticalVertices);

  if (!scene) {
    std::cout << "Model  failed to load from  " << filename << "error found  "
              << importer.GetErrorString() << "\n";
    return;
  }

  LoadNode(scene->mRootNode, scene);

  LoadMaterials(scene);
}

void Model::LoadNode(aiNode *node, const aiScene *scene) {
  for (size_t i = 0; i < node->mNumMeshes; i++) {
    LoadMesh(scene->mMeshes[node->mMeshes[i]], scene);
  }

  for (size_t i = 0; i < node->mNumChildren; i++) {
    LoadNode(node->mChildren[i], scene);
  }
}

void Model::LoadMesh(aiMesh *mesh, const aiScene *scene) {
  std::vector<GLfloat> vertices;
  std::vector<unsigned int> indices;

  for (size_t i = 0; i < mesh->mNumVertices; i++) {
    vertices.insert(vertices.end(), {mesh->mVertices[i].x, mesh->mVertices[i].y,
                                     mesh->mVertices[i].z});
    if (mesh->mTextureCoords[0]) {
      vertices.insert(vertices.end(), {mesh->mTextureCoords[0][i].x,
                                       mesh->mTextureCoords[0][i].y});
    } else {
      vertices.insert(vertices.end(), {0.0f, 0.0f});
    }
    vertices.insert(vertices.end(), {-mesh->mNormals[i].x, -mesh->mNormals[i].y,
                                     -mesh->mNormals[i].z});
  }

  for (size_t i = 0; i < mesh->mNumFaces; i++) {
    aiFace face = mesh->mFaces[i];
    for (size_t j = 0; j < face.mNumIndices; j++) {
      indices.push_back(face.mIndices[j]);
    }
  }

  Mesh *newMesh = new Mesh();
  newMesh->Create_Mesh(&vertices[0], &indices[0], vertices.size(),
                       indices.size());
  meshlist.push_back(newMesh);
  meshtotexture.push_back(mesh->mMaterialIndex);
}

void Model::LoadMaterials(const aiScene *scene) {
  texturelist.resize(scene->mNumMaterials);

  for (size_t i = 0; i < scene->mNumMaterials; i++) {
    aiMaterial *material = scene->mMaterials[i];

    texturelist[i] = nullptr;

    if (material->GetTextureCount(aiTextureType_DIFFUSE)) {
      aiString path;
      if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {
        int idx = std::string(path.data).rfind("\\");
        std::string filename = std::string(path.data).substr(idx + 1);
        {
          uint pos = filename.rfind(".");
          std::string temp = filename.substr(pos);
          filename.replace(pos, temp.size() + 1, str_tolower(temp));
          std::cout << filename << "\n";
        }
        std::string texPath = "../" + std::string("texture/") + filename;

        texturelist[i] = new Texture(texPath.c_str());

        if (texturelist[i]->Load_texture()) {
          std::cout << "Failed to load texture at: " << texPath << "\n";
          delete texturelist[i];
          texturelist[i] = nullptr;
        }
      }
    }

    if (!texturelist[i]) {
      texturelist[i] = new Texture("../texture/plain.png");
      texturelist[i]->Load_textureA();
    }
  }
}

void Model::ClearModel() {
  for (size_t i = 0; i < meshlist.size(); i++) {
    if (meshlist[i]) {
      delete meshlist[i];
      meshlist[i] = nullptr;
    }
  }

  for (size_t i = 0; i < texturelist.size(); i++) {
    if (texturelist[i]) {
      delete texturelist[i];
      texturelist[i] = nullptr;
    }
  }
}

Model::~Model() { ClearModel(); }
