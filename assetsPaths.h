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

#ifndef PROJECT_TELEPORT_ASSETSPATHS_H
#define PROJECT_TELEPORT_ASSETSPATHS_H

#include <string>
#include <vector>

namespace assetsPaths {
    const std::string cubeObject = "../assets/cube.obj";

    const std::string concreteTexture = "../assets/concrete.jpg";
    const std::string carpetTexture = "../assets/concrete.jpg";

    const std::vector<std::string> skyboxTextures = {
            "../assets/skybox/TropicalSunnyDay/TropicalSunnyDayBack2048.png",
            "../assets/skybox/TropicalSunnyDay/TropicalSunnyDayFront2048.png",
            "../assets/skybox/TropicalSunnyDay/TropicalSunnyDayRight2048.png",
            "../assets/skybox/TropicalSunnyDay/TropicalSunnyDayLeft2048.png",
            "../assets/skybox/TropicalSunnyDay/TropicalSunnyDayUp2048.png",
            "../assets/skybox/TropicalSunnyDay/TropicalSunnyDayDown2048.png"
    };

    struct Shader {
        const std::string vertex;
        const std::string fragment;
    };

    const Shader cubeMapShader = {"../shaders/cubeMap.vert",
                                  "../shaders/cubeMap.frag"};

    const Shader texturedShader = {"../shaders/textured.vert",
                                  "../shaders/textured.frag"};
};

#endif // PROJECT_TELEPORT_ASSETSPATHS_H
