/**
 * This file is part of Project Teleport, a game written in C++ using the SDL2
 * library and OpenGL API.
 *
 * Copyright (C) 2018 Jakub Gembacz
 * Copyright (C) 2018 Pierre Gillet
 * Copyright (C) 2018 Jamie McKechnie
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

#ifndef PROJECT_TELEPORT_SHADER_H
#define PROJECT_TELEPORT_SHADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    unsigned int ID;

    // constructor generates the shader on the fly
    Shader(const char *vertexPath, const char *fragmentPath,
           const char *geometryPath = nullptr);

    // Activate the shader
    void use();

    // Utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

    void setVec2(const std::string &name, const glm::vec2 &value) const;
    void setVec2(const std::string &name, float x, float y) const;

    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;

    void setVec4(const std::string &name, const glm::vec4 &value) const;
    void setVec4(const std::string &name, float x, float y, float z, float w);

    void setMat2(const std::string &name, const glm::mat2 &mat) const;
    void setMat3(const std::string &name, const glm::mat3 &mat) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
    // utility function for checking shader compilation/linking errors.
    void checkCompileErrors(GLuint shader, std::string type);
};

#endif // PROJECT_TELEPORT_SHADER_H

//#ifndef PROJECT_TELEPORT_SHADER_H
//#define PROJECT_TELEPORT_SHADER_H
//
//#include <GL/glew.h>
//#include <string>
//
//#include "rt3d.h"
//
//
//class Shader {
//public:
//    Shader();
//
//    GLuint initialize(const std::string & vertexShaderPath,
//                      const std::string & fragmentShaderPath);
//    void use();
//    void setUniformMatrix4fv(const char* uniformName, const GLfloat *data);
//
//    GLuint getId();
//
//private:
//    GLuint id;
//};
//
//
//#endif // PROJECT_TELEPORT_SHADER_H
