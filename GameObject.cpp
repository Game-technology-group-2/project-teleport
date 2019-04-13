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

#include "GameObject.h"

#include "GraphicsComponent.h"
#include "InputComponent.h"

#include <utility>


GameObject::GameObject(std::shared_ptr<InputComponent> input,
                       std::shared_ptr<PhysicsComponent> physics,
                       std::shared_ptr<GraphicsComponent> graphics,
                       glm::vec3 position)
        : inputComponent(std::move(input)), physicsComponent(std::move(physics)),
          graphicsComponent(std::move(graphics)), position(position) {

}

void GameObject::update(Graphics & graphics) {
    inputComponent->update(*this);
    physicsComponent->update(*this);
    graphicsComponent->update(*this, graphics);
}

glm::vec3 GameObject::getPosition() const {
    return position;
}

void GameObject::setPosition(const glm::vec3 & position) {
    this->position = position;
}

Helpers::Direction GameObject::getDirection() const {
    return direction;
}

void GameObject::setDirection(Helpers::Direction direction) {
    this->direction = direction;
}

void GameObject::setVelocity(int velocity) {
    this->velocity = velocity;
}

std::shared_ptr<InputComponent> GameObject::getInputComponent() const {
    return inputComponent;
}

std::shared_ptr<PhysicsComponent> GameObject::getPhysicsComponent() const {
    return physicsComponent;
}

std::shared_ptr<GraphicsComponent> GameObject::getGraphicsComponent() const {
    return graphicsComponent;
}
