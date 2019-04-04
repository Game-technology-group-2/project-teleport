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
public:
    Player(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = Constants::DefaultCameraValues::yaw,
           float pitch = Constants::DefaultCameraValues::pitch);

    void setMovementDirection(Helpers::Direction direction);

//    void move(Helpers::Direction direction, float deltaTime);
    void processMouseMovement(float xOffset, float yoffset,
                              GLboolean constrainPitch = true);
    float getZoom() const;
    glm::mat4 getViewMatrix();

private:
    Camera camera;
    Helpers::Direction movementDirection;
};

#endif //PROJECT_TELEPORT_PLAYER_H
