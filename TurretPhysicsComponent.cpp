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

#include "TurretPhysicsComponent.h"

#include "Constants.h"
#include "Helpers.h"

#include <iostream>
#include <utility>


TurretPhysicsComponent::TurretPhysicsComponent(glm::vec3 worldUp, float yaw,
                                               float pitch)
        : worldUp(worldUp), yaw(yaw), pitch(pitch) {
    updateVectors();
}

void TurretPhysicsComponent::update(GameObject & gameObject) {
    updateVectors();
}

void TurretPhysicsComponent::updateVectors() {
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);
    // Normalize the vectors, because their length gets closer to 0
    // the more you look up or down which results in slower movement.
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

const glm::vec3 & TurretPhysicsComponent::getFront() const {
    return front;
}

const glm::vec3 & TurretPhysicsComponent::getUp() const {
    return up;
}
