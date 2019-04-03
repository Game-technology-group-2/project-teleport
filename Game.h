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

#ifndef PROJECT_TELEPORT_GAME_H
#define PROJECT_TELEPORT_GAME_H

#include <GL/glew.h>
#include <memory>
#include <SDL2/SDL.h>
#include <vector>

#include "assetsPaths.h"
#include "Camera.h"
#include "Mesh.h"
#include "Model.h"
#include "Player.h"
#include "Shader.h"


class Game {
public:
    Game();
    ~Game();
    void runEventLoop();

private:
    SDL_Window *mainWindow; // window handle
    SDL_GLContext mainContext; // OpenGL context handle
    unsigned int mainWindowWidth;
    unsigned int mainWindowHeight;
//    std::shared_ptr<Shader> skyboxShader;
//    std::shared_ptr<Shader> textureShader;
//    std::shared_ptr<Shader> colorInterpolationShader;
    std::shared_ptr<Shader> modelLoadingShader;
//    std::vector<Mesh> meshObjects;
//    std::vector<GLuint> textures;
    std::vector<Model> models;
    std::vector<GLuint> skybox = std::vector<GLuint>(6);
//    Player player = Player(glm::vec3(-2.0f, 1.0f, 8.0f),
//                           glm::vec3(0.0f, 1.0f, -1.0f),
//                           glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
//    Player player = Player(glm::vec3(-2.0f, 1.0f, 8.0f),
//                           glm::vec3(0.0f, 1.0f, 0.0f),
//                           0.0f, 0.0f);
//    Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    Player player {glm::vec3(0.0f, 0.0f, 3.0f)};

    void initializeGlew();
    void setupRenderingContext();
    void init();
    void loadShaders();
    void handleWindowEvent(const SDL_WindowEvent & windowEvent);
    void handleUserInput();
    void draw();
};


#endif // PROJECT_TELEPORT_GAME_H
