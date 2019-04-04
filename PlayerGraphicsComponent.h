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

#ifndef PROJECT_TELEPORT_PLAYERGRAPHICSCOMPONENT_H
#define PROJECT_TELEPORT_PLAYERGRAPHICSCOMPONENT_H

#include "Camera.h"
#include "Graphics.h"
#include "GraphicsComponent.h"


class PlayerGraphicsComponent : public GraphicsComponent {
public:
    PlayerGraphicsComponent(const Camera & camera);
    void update(GameObject & obj, Graphics & graphics) override;

private:
    Camera camera;
};


#endif //PROJECT_TELEPORT_PLAYERGRAPHICSCOMPONENT_H
