/**
 * This file is part of Project Teleport, a game written in C++ using the SDL2
 * library and OpenGL API.
 *
 * Copyright (C) 2018 Jakub Gembacz
 * Copyright (C) 2018 Pierre Gillet
 * Copyright (C) 2018 Jamie McKechnie
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

#ifndef AGP_GROUP_PROJECT_CONSTANTS_H
#define AGP_GROUP_PROJECT_CONSTANTS_H

#include <glm/glm.hpp>

namespace Constants {
    namespace BaseWindowSize {
        const int width = 800;
        const int height = 600;
    }

    const double degreeToRadian = 0.017453293;
    const glm::vec3 spawnPosition = {0.0f, 1.0f, 0.0f};//-2.0f, 1.0f, 8.0f};
    const glm::vec3 teleport1 = {8.0f, 1.0f, 8.0f};
    const glm::vec3 teleport2 = {-10.0f, 1.0f, -12.0f};
}

#endif //AGP_GROUP_PROJECT_CONSTANTS_H
