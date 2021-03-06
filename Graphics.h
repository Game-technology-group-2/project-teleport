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

#ifndef PROJECT_TELEPORT_GRAPHICS_H
#define PROJECT_TELEPORT_GRAPHICS_H

#include "Model.h"
#include "PlayerPhysicsComponent.h"
#include "Shader.h"

#include <GL/glew.h>
#include <memory>
#include <SDL2/SDL.h>
#include <vector>


class Graphics {
public:
    Graphics(unsigned int mainWindowWidth, unsigned int mainWindowHeight,
             float zoom, std::shared_ptr<GameObject> player,
             std::shared_ptr<PlayerPhysicsComponent> playerPhysics);
    ~Graphics();
    void draw(Model model, glm::vec3 position, glm::vec3 scale);
    void renderFrame();
    void handleWindowEvent(const SDL_WindowEvent & windowEvent);

private:
    SDL_Window * mainWindow;
    SDL_GLContext mainContext;
    unsigned int mainWindowWidth;
    unsigned int mainWindowHeight;
    float zoom;
    std::shared_ptr<Shader> modelLoadingShader;
//    std::vector<GLuint> skybox = std::vector<GLuint>(6);
    std::shared_ptr<GameObject> player;
    std::shared_ptr<PlayerPhysicsComponent> playerPhysics;

    void loadModels();
    void initializeGlew();
    void setupRenderingContext();
    void loadShaders();
    glm::mat4 getViewMatrix();
};


#endif //PROJECT_TELEPORT_GRAPHICS_H
