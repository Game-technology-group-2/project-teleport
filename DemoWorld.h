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

#ifndef PROJECT_TELEPORT_DEMOWORLD_H
#define PROJECT_TELEPORT_DEMOWORLD_H

#include "GameObject.h"
#include "World.h"

#include <vector>


class DemoWorld : public World {
public:
    DemoWorld();

    void update() override;

    const std::shared_ptr<Graphics> & getGraphics() const override;

private:
    // "player" is special (it's the camera and all), so it's apart from the
    // worldObjects vector to avoid mistakes such as deleting it.
    // I know this is a code smell. It should be refactored later.
    std::shared_ptr<GameObject> player;
    std::shared_ptr<Graphics> graphics;
    std::vector<GameObject> worldObjects;
};


#endif //PROJECT_TELEPORT_DEMOWORLD_H

