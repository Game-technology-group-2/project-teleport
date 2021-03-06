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

#ifndef PROJECT_TELEPORT_TURRETPHYSICSCOMPONENT_H
#define PROJECT_TELEPORT_TURRETPHYSICSCOMPONENT_H

#include "PhysicsComponent.h"

#include <memory>


class TurretPhysicsComponent : public PhysicsComponent {
public:
    TurretPhysicsComponent(glm::vec3 worldUp, float yaw, float pitch);

    void update(GameObject & gameObject) override;

    const glm::vec3 & getFront() const;

    const glm::vec3 & getUp() const;

private:
    float yaw;
    float pitch;
    glm::vec3 worldUp;
    glm::vec3 up {};
    glm::vec3 front {};
    glm::vec3 right {};

    void updateVectors();
};


#endif //PROJECT_TELEPORT_TURRETPHYSICSCOMPONENT_H
