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
#include <string>

#include "rt3d.h"


class Shader {
public:
    Shader();

    void initialize(const std::string & vertexShaderPath,
                    const std::string & fragmentShaderPath);
    void use();
    void setUniformMatrix4fv(const char* uniformName, const GLfloat *data);

    GLuint getId();

private:
    GLuint id;
};


#endif // PROJECT_TELEPORT_SHADER_H
