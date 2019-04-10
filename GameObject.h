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

#ifndef PROJECT_TELEPORT_GAMEOBJECT_H
#define PROJECT_TELEPORT_GAMEOBJECT_H

#include "Helpers.h"

#include <glm/vec3.hpp>
#include <memory>


class Graphics;
class InputComponent;
class GraphicsComponent;
class PhysicsComponent;

class GameObject {
public:
    GameObject(InputComponent * input,
               PhysicsComponent * physics,
               GraphicsComponent * graphics,
               glm::vec3 position);

    virtual ~GameObject();

    void update(Graphics & graphics);

    glm::vec3 getPosition() const;
    void setPosition(const glm::vec3 & position);

    Helpers::Direction getDirection() const;
    void setDirection(Helpers::Direction direction);

    void setVelocity(int velocity);

    InputComponent * getInputComponent() const;

    GraphicsComponent * getGraphicsComponent() const;

    PhysicsComponent * getPhysicsComponent() const;

private:
    glm::vec3 position;
    Helpers::Direction direction;
    int velocity;
    InputComponent * inputComponent;
    PhysicsComponent * physicsComponent;
    GraphicsComponent * graphicsComponent;
};


#endif //PROJECT_TELEPORT_GAMEOBJECT_H
