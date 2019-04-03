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

#include "Player.h"

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Constants.h"
#include "Helpers.h"


Player::Player(glm::vec3 position, glm::vec3 up, float yaw, float pitch) {
    Camera(position, up, yaw, pitch);
}

void Player::move(Helpers::Movement direction, float deltaTime) {
    camera.move(direction, deltaTime);
}

void Player::processMouseMovement(float xOffset, float yoffset,
                                  GLboolean constrainPitch) {
    camera.processMouseMovement(xOffset, yoffset, constrainPitch);
}

float Player::getZoom() const {
    return camera.getZoom();
}

glm::mat4 Player::getViewMatrix() {
    return camera.getViewMatrix();
}

void Player::setMovementDirection(Helpers::Movement direction) {
    movementDirection = direction;
}
