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

#include <iostream>
#include <utility>


PlayerPhysicsComponent::PlayerPhysicsComponent(std::shared_ptr<Camera> camera)
        : camera(std::move(camera)) {
    updateVectors();
}

void PlayerPhysicsComponent::update(GameObject & gameObject) {
    using namespace Helpers;
    float velocity = movementSpeed * Constants::MS_PER_FRAME;

    auto position {gameObject.getPosition()};
    switch (gameObject.getDirection()) {
        case Direction::FORWARD:
//            std::cout << "F" << std::endl;
            gameObject.setPosition(position + front * velocity);
            break;

        case Direction::BACKWARD:
//            std::cout << "B" << std::endl;
            gameObject.setPosition(position - front * velocity);
            break;

        case Direction::LEFT:
//            std::cout << "L" << std::endl;
            gameObject.setPosition(position - right * velocity);
            break;

        case Direction::RIGHT:
//            std::cout << "R" << std::endl;
            gameObject.setPosition(position + right * velocity);
            break;

        default:
//            std::cout << "D" << std::endl;
            break;
    }

    updateVectors();

//    std::cout << "{" << gameObject.getPosition().x
//              << ", " << gameObject.getPosition().y
//              << ", " << gameObject.getPosition().z
//              << "}" << std::endl;
}

void PlayerPhysicsComponent::updateVectors() {
    auto yaw {camera->getYaw()};
    auto pitch {camera->getPitch()};
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

const glm::vec3 & PlayerPhysicsComponent::getUp() const {
    return up;
}
