/**
 * This file is part of Project Teleport, a game written in C++ using the SDL2
 * library and OpenGL API.
 *
 * Copyright (C) 2018 Pierre Gillet
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

#ifndef PROJECT_TELEPORT_PLAYER_H
#define PROJECT_TELEPORT_PLAYER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Constants.h"
#include "Camera.h"

class Player {
private:
//    glm::vec3 eye;
//    glm::vec3 at;
//    glm::vec3 up;
//    GLfloat rotation;
//    Camera camera;

public:
    Camera camera;

//    Player(glm::vec3 eye, glm::vec3 at, glm::vec3 up, GLfloat r);
    Player(glm::vec3 position, glm::vec3 up, float yaw, float pitch);
    void moveForward(GLfloat distance);
    void moveRight(GLfloat distance);
    void moveUp(GLfloat distance);
    void lookRight(GLfloat distance);
//    void teleport(glm::vec3 newPosition);
//    glm::mat4 getCameraDirection();
};

#endif //PROJECT_TELEPORT_PLAYER_H
