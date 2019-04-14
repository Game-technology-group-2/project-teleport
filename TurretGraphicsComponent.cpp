#include <utility>

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

#include "TurretGraphicsComponent.h"


TurretGraphicsComponent::TurretGraphicsComponent(std::shared_ptr<Model> model)
        : model(std::move(model)) {

}

void TurretGraphicsComponent::update(GameObject & obj, Graphics & graphics) {
    graphics.draw(*model, glm::vec3{0.0f, -1.75f, 0.0f}, glm::vec3{0.2f, 0.2f, 0.2f});
}
