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

#include "Game.h"

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include <stack>

#include "assetsPaths.h"
#include "Constants.h"
#include "Mesh.h"
#include "Model.h"
#include "Shader.h"


Game::Game() {
    // Create window and render context
    this->mainWindowWidth = Constants::BaseWindowSize::width;
    this->mainWindowHeight = Constants::BaseWindowSize::height;
    this->setupRenderingContext();
    this->initializeGlew();
    this->init();
}

Game::~Game() {
    SDL_GL_DeleteContext(this->mainContext);
    SDL_DestroyWindow(this->mainWindow);
    SDL_Quit();
}

void Game::runEventLoop() {
    bool running {true};

    while (running) {
        auto startTime {SDL_GetTicks()};
        SDL_Event sdlEvent;
        while (SDL_PollEvent(&sdlEvent)) {
            switch (sdlEvent.type) {
                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_WINDOWEVENT:
                    this->handleWindowEvent(sdlEvent.window);
                    break;

                default:
                    break;
            }
        }
        this->handleUserInput();
        this->draw(); // call the draw function

        auto currentTime {SDL_GetTicks()};
        auto maximumTime {startTime + Constants::MS_PER_FRAME};
        // Only wait if going faster than the expected update rate
        if (currentTime < maximumTime) {
            SDL_Delay(maximumTime - currentTime);
        }
    }
}

void Game::initializeGlew() {
#ifdef _WIN32
    // Required on Windows *only* init GLEW to access OpenGL beyond 1.1
    glewExperimental = GL_TRUE;
#endif
    GLenum err {glewInit()};
    if (GLEW_OK != err) {
        throw std::runtime_error("glewInit failed : "
                                 + std::string(reinterpret_cast<const char*>(glewGetErrorString(err))));
    }
}

void Game::setupRenderingContext() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) // Initialize video
        throw std::runtime_error("Unable to initialize SDL : "
                                 + std::string(SDL_GetError()));

    // Request an OpenGL 3.0 context.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);  // double buffering on
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8); // 8 bit alpha buffering
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    // Turn on x4 multisampling anti-aliasing (MSAA)
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

    this->mainWindow = SDL_CreateWindow("Project Teleport",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        this->mainWindowWidth,
                                        this->mainWindowHeight,
                                        SDL_WINDOW_OPENGL
                                        | SDL_WINDOW_RESIZABLE
                                        | SDL_WINDOW_SHOWN);

    if (!this->mainWindow) {
        throw std::runtime_error("Unable to create window : "
                                 + std::string(SDL_GetError()));
    }

    auto relativeMouseMode = SDL_SetRelativeMouseMode(SDL_TRUE);
    if (relativeMouseMode) {
        throw std::runtime_error("Unable to capture the mouse : "
                                 + std::string(SDL_GetError()));
    }

    // Create openGL context and attach to window
    this->mainContext = SDL_GL_CreateContext(this->mainWindow);

    int swapIntervalReturn = SDL_GL_SetSwapInterval(0);
    if (swapIntervalReturn) {
        throw std::runtime_error("Could not set swap interval : "
                                 + std::string(SDL_GetError()));
    }
}

void Game::init() {
    this->loadShaders();

//    loadCubeMap(assetsPaths::skyboxTextures, this->skybox);
//
//    textures = {loadTexture(assetsPaths::concreteTexture),
//                loadTexture(assetsPaths::carpetTexture),};

//    meshObjects = {Mesh(assetsPaths::cubeObject),};

    this->models = {Model(assetsPaths::cubeModel),
                    Model(assetsPaths::deskModel),
                    Model(assetsPaths::nanosuitModel)};
//    this->player = Player(Constants::spawnPosition, // glm::vec3(-2.0f, 1.0f, 8.0f),
//                          glm::vec3(0.0f, 1.0f, 0.0f),
//                          0.0f, 0.0f);

    glEnable(GL_DEPTH_TEST);
}

void Game::loadShaders() {
//    Shader skybox = Shader(assetsPaths::cubeMapShader.vertex.c_str(),
//                           assetsPaths::cubeMapShader.fragment.c_str());
//    Shader textured = Shader(assetsPaths::texturedShader.vertex.c_str(),
//                             assetsPaths::texturedShader.fragment.c_str());
//    Shader colorInterpolation = Shader(assetsPaths::colorInterpolationShader.vertex.c_str(),
//                                       assetsPaths::colorInterpolationShader.fragment.c_str());
    this->modelLoadingShader = std::make_shared<Shader>(assetsPaths::modelLoadingShader.vertex.c_str(),
                                                        assetsPaths::modelLoadingShader.fragment.c_str());
}

void Game::handleWindowEvent(const SDL_WindowEvent & windowEvent) {
    if (SDL_WINDOWEVENT_SIZE_CHANGED == windowEvent.event) {
        this->mainWindowWidth = (unsigned int) windowEvent.data1;
        this->mainWindowHeight = (unsigned int) windowEvent.data2;
        glViewport(0, 0, this->mainWindowWidth, this->mainWindowHeight);
    }
}

void Game::handleUserInput() {
    // Todo : Handle KeyPresses events instead of checking if the key is
    //  pressed each loop, or find a better way to structure this function
    const Uint8 *keys = SDL_GetKeyboardState(nullptr);
    if (keys[SDL_SCANCODE_W]) camera.move(Helpers::Movement::FORWARD, 0.1f);
    if (keys[SDL_SCANCODE_S]) camera.move(Helpers::Movement::BACKWARD, 0.1f);
    if (keys[SDL_SCANCODE_A]) camera.move(Helpers::Movement::LEFT, 0.1f);
    if (keys[SDL_SCANCODE_D]) camera.move(Helpers::Movement::RIGHT, 0.1f);

    if (keys[SDL_SCANCODE_1]) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDisable(GL_CULL_FACE);
    }

    if (keys[SDL_SCANCODE_2]) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable(GL_CULL_FACE);
    }

//    if (keys[SDL_SCANCODE_3]) this->player.teleport(Constants::spawnPosition);
//
//    if (keys[SDL_SCANCODE_4]) this->player.teleport(Constants::teleport1);
//
//    if (keys[SDL_SCANCODE_5]) this->player.teleport(Constants::teleport2);

    int x {0};
    int y {0};
    SDL_GetRelativeMouseState(&x, &y);
    this->camera.processMouseMovement(x, y, true);
}

void Game::draw() {
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    glDisable(GL_CULL_FACE);

    // don't forget to enable shader before setting uniforms
    this->modelLoadingShader->use();

    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(this->camera.Zoom),
                                            (float)this->mainWindowWidth / (float)this->mainWindowHeight,
                                            0.1f, 100.0f);
    glm::mat4 view = this->camera.getViewMatrix();
    this->modelLoadingShader->setMat4("projection", projection);
    this->modelLoadingShader->setMat4("view", view);

    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down

    this->modelLoadingShader->setMat4("model", model);
    models[1].draw(*(this->modelLoadingShader));

    glUseProgram(0);
    SDL_GL_SwapWindow(this->mainWindow); // swap buffers
}
