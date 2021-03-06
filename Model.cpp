/**
 * This file is part of Project Teleport, a game written in C++ using the SDL2
 * library and OpenGL API.
 *
 * Copyright (C) 2018 Pierre Gillet
 *
 * Copyright (C) 2018 Joey de Vries (https://twitter.com/JoeyDeVriez)
 * https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/mesh.h
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


#include "Model.h"

#include "Mesh.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <string>

Model::Model(const std::string & path, bool gamma)
        : gammaCorrection(gamma) {
        loadModel(path);
}

void Model::draw(Shader shader) {
    for (unsigned int i {0}; i < meshes.size(); i++) {
        meshes[i].draw(shader);
    }
}

void Model::loadModel(const std::string & path) {
    // read file via ASSIMP
    Assimp::Importer importer;
    const aiScene * scene {importer.ReadFile(path, aiProcess_Triangulate |
                                                   aiProcess_FlipUVs |
                                                   aiProcess_CalcTangentSpace)};

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::string error {importer.GetErrorString()};
        throw std::runtime_error("Assimp error : " + error);
    }
    // Retrieve the directory path of the filepath
    directory = path.substr(0, path.find_last_of('/'));

    // Process ASSIMP's root node recursively
    processNode(scene->mRootNode, scene);
}

// Processes a node in a recursive fashion.
// Processes each individual mesh located at the node and repeats this process
// on its children nodes (if any).
void Model::processNode(aiNode * node, const aiScene * scene) {
    // Process each mesh located at the current node
    for (unsigned int i {0}; i < node->mNumMeshes; i++) {
        // the node object only contains indices to index the actual objects in the scene.
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh * mesh {scene->mMeshes[node->mMeshes[i]]};
        meshes.push_back(processMesh(mesh, scene));
    }
    // After we've processed all of the meshes (if any)
    // we then recursively process each of the children nodes
    for (unsigned int i {0}; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh * mesh, const aiScene * scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    // Walk through each of the mesh's vertices
    for (unsigned int i {0}; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        // we declare a placeholder vector since assimp uses its own
        // vector class that doesn't directly convert to glm's vec3 class
        // so we transfer the data to this placeholder glm::vec3 first.
        glm::vec3 vector;

        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;

        if (mesh->mTextureCoords[0]) {
            glm::vec2 vec;
            // A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        } else {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }

        vector.x = mesh->mTangents[i].x;
        vector.y = mesh->mTangents[i].y;
        vector.z = mesh->mTangents[i].z;
        vertex.Tangent = vector;

        vector.x = mesh->mBitangents[i].x;
        vector.y = mesh->mBitangents[i].y;
        vector.z = mesh->mBitangents[i].z;
        vertex.Bitangent = vector;
        vertices.push_back(vertex);
    }

    // Now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        // Retrieve all indices of the face and store them in the indices vector
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    // Process materials
    aiMaterial * material {scene->mMaterials[mesh->mMaterialIndex]};
    // We assume a convention for sampler names in the shaders.
    // Each diffuse texture should be named as 'texture_diffuseN'
    // where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN

    // 1. diffuse maps
    std::vector<Texture> diffuseMaps {loadMaterialTextures(material,
                                                           aiTextureType_DIFFUSE,
                                                           "texture_diffuse")};
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    std::vector<Texture> specularMaps {loadMaterialTextures(material,
                                                            aiTextureType_SPECULAR,
                                                            "texture_specular")};
    textures.insert(textures.end(), specularMaps.begin(),
                    specularMaps.end());
    // 3. normal maps
    std::vector<Texture> normalMaps {loadMaterialTextures(material,
                                                          aiTextureType_HEIGHT,
                                                          "texture_normal")};
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    std::vector<Texture> heightMaps {loadMaterialTextures(material,
                                                          aiTextureType_AMBIENT,
                                                          "texture_height")};
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    return Mesh(vertices, indices, textures);
}

// Checks all material textures of a given type and loads the textures
// if they're not loaded yet. The required info is returned as a Texture struct.
std::vector<Texture> Model::loadMaterialTextures(aiMaterial * mat,
                                                 aiTextureType type,
                                                 const std::string & typeName) {
    std::vector<Texture> textures;
    for (unsigned int i {0}; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        // Check if texture was loaded before and if so,
        // continue to next iteration: skip loading a new texture
        bool skip {false};
        for (auto & j : textures_loaded) {
            if (0 == std::strcmp(j.path.data(), str.C_Str())) {
                textures.push_back(j);
                skip = true;
                break;
            }
        }

        // If texture hasn't been loaded already, load it
        if (!skip) {
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), this->directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            // Store it as texture loaded for entire model
            // to ensure we won't unnecessarily load duplicate textures.
            textures_loaded.push_back(texture);
        }
    }
    return textures;
}

unsigned int TextureFromFile(const char * path, const std::string & directory,
                             bool gamma) {
    auto filename {std::string(path)};
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char * data {stbi_load(filename.c_str(), &width, &height,
                                    &nrComponents, 0)};
    if (data) {
        GLenum format {};
        if (1 == nrComponents)
            format = GL_RED;
        else if (3 == nrComponents)
            format = GL_RGB;
        else if (4 == nrComponents)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        std::cerr << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
