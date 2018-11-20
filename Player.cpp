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

#include "Player.h"

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "constants.h"

Player::Player(glm::vec3 eye, glm::vec3 at, glm::vec3 up, GLfloat r)
        : eye(eye), at(at), up(up), rotation(r) {

}
void Player::moveForward(GLfloat distance) {
    eye = glm::vec3(eye.x + distance * std::sin(rotation * Constants::degreeToRadian),
                    eye.y, eye.z - distance * std::cos(rotation * Constants::degreeToRadian));
}

void Player::moveRight(GLfloat distance) {
    eye = glm::vec3(eye.x + distance * std::cos(rotation * Constants::degreeToRadian),
                    eye.y, eye.z + distance * std::sin(rotation * Constants::degreeToRadian));
}

void Player::moveUp(GLfloat distance) {
    eye.y += distance;
}

void Player::lookRight(GLfloat distance) {
    rotation += distance;
}

glm::mat4 Player::getCameraDirection() {
    glm::vec3 direction = glm::vec3(eye.x + 1.0f * std::sin(rotation * Constants::degreeToRadian), eye.y, eye.z - 1.0f * std::cos(rotation * Constants::degreeToRadian));
    return glm::lookAt(eye, direction, up);
}