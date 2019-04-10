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

#include "PlayerPhysicsComponent.h"

#include "Constants.h"
#include "Helpers.h"


PlayerPhysicsComponent::PlayerPhysicsComponent()
        : movementSpeed(Constants::DefaultCameraValues::speed) {
    glm::vec3 newFront;
    auto pitch {Constants::DefaultCameraValues::pitch};
    auto yaw {Constants::DefaultCameraValues::yaw};
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);
    right = glm::normalize(glm::cross(front, worldUp));
}

void PlayerPhysicsComponent::update(GameObject & gameObject) {
    using namespace Helpers;
    float velocity = movementSpeed * Constants::MS_PER_FRAME;

    switch (gameObject.getDirection()) {
        case Direction::FORWARD:
            gameObject.setPosition(gameObject.getPosition() + front * velocity);
            break;

        case Direction::BACKWARD:
            gameObject.setPosition(gameObject.getPosition() - front * velocity);
            break;

        case Direction::LEFT:
            gameObject.setPosition(gameObject.getPosition() - right * velocity);
            break;

        case Direction::RIGHT:
            gameObject.setPosition(gameObject.getPosition() + right * velocity);
            break;

        default:
            break;
    }
}

const glm::vec3 & PlayerPhysicsComponent::getFront() const {
    return front;
}

void PlayerPhysicsComponent::setFront(const glm::vec3 & front) {
    PlayerPhysicsComponent::front = front;
}

const glm::vec3 & PlayerPhysicsComponent::getRight() const {
    return right;
}

void PlayerPhysicsComponent::setRight(const glm::vec3 & right) {
    PlayerPhysicsComponent::right = right;
}

const glm::vec3 & PlayerPhysicsComponent::getWorldUp() const {
    return worldUp;
}
