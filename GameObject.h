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

#include <glm/vec3.hpp>
#include <memory>

#include "InputComponent.h"
#include "GraphicsComponent.h"


class InputComponent;
class GraphicsComponent;

class GameObject {
private:
    glm::vec3 Position;
    int velocity;
    std::shared_ptr<InputComponent> inputComponent;
    std::shared_ptr<GraphicsComponent> graphicsComponent;

    GameObject(std::shared_ptr<InputComponent> input,
               std::shared_ptr<GraphicsComponent> graphics);

public:
    void update();
};


#endif //PROJECT_TELEPORT_GAMEOBJECT_H
