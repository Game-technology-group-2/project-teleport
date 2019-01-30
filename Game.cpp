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

#include "Game.h"

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <stack>
#ifdef _WIN32
#include <SDL.h>
#endif
#ifndef _WIN32
#include <SDL2/SDL.h>
#endif

//#include "assetsLoader.h"
#include "assetsPaths.h"
#include "constants.h"
#include "Mesh.h"
#include "Model.h"
#include "rt3dObjLoader.h"
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
    SDL_Event sdlEvent;
    bool running = true;

    while (running) {
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
    }
}

void Game::initializeGlew() {
#ifdef _WIN32
    // Required on Windows *only* init GLEW to access OpenGL beyond 1.1
    glewExperimental = GL_TRUE;
#endif
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cout << "glewInit failed, aborting." << std::endl;
        exit(1);
    }
    std::cout << glGetString(GL_VERSION) << std::endl;
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

    this->mainWindow = SDL_CreateWindow("SDL/GLM/OpenGL Demo",
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

    // Create openGL context and attach to window
    this->mainContext = SDL_GL_CreateContext(this->mainWindow);
    // set swap buffers to sync with monitor's vertical refresh rate
    SDL_GL_SetSwapInterval(1);
}

void Game::init() {
    this->loadShaders();

//    loadCubeMap(assetsPaths::skyboxTextures, this->skybox);
//
//    textures = {loadTexture(assetsPaths::concreteTexture),
//                loadTexture(assetsPaths::carpetTexture),};

//    meshObjects = {Mesh(assetsPaths::cubeObject),};

    this->models = {};
    this->player = Player(Constants::spawnPosition, // glm::vec3(-2.0f, 1.0f, 8.0f),
                          glm::vec3(0.0f, 1.0f, -1.0f),
                          glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Game::loadShaders() {
    Shader skybox = Shader(assetsPaths::cubeMapShader.vertex.c_str(),
                           assetsPaths::cubeMapShader.fragment.c_str());
    Shader textured = Shader(assetsPaths::texturedShader.vertex.c_str(),
                             assetsPaths::texturedShader.fragment.c_str());
    this->skyboxShader = &skybox;
    this->textureShader = &textured;

//    this->skyboxShader.initialize(assetsPaths::cubeMapShader.vertex,
//                                  assetsPaths::cubeMapShader.fragment);
//
//    this->textureShader.initialize(assetsPaths::texturedShader.vertex,
//                                   assetsPaths::texturedShader.fragment);
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
    if (keys[SDL_SCANCODE_W]) player.moveForward(0.1f);
    if (keys[SDL_SCANCODE_S]) player.moveForward(-0.1f);
    if (keys[SDL_SCANCODE_A]) player.moveRight(-0.1f);
    if (keys[SDL_SCANCODE_D]) player.moveRight(0.1f);
    if (keys[SDL_SCANCODE_R]) player.moveUp(0.1f);
    if (keys[SDL_SCANCODE_F]) player.moveUp(-0.1f);

    if (keys[SDL_SCANCODE_Q]) player.lookRight(-1.0f);
    if (keys[SDL_SCANCODE_E]) player.lookRight(1.0f);

    if (keys[SDL_SCANCODE_1]) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDisable(GL_CULL_FACE);
    }

    if (keys[SDL_SCANCODE_2]) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable(GL_CULL_FACE);
    }

    if (keys[SDL_SCANCODE_3]) this->player.teleport(Constants::spawnPosition);

    if (keys[SDL_SCANCODE_4]) this->player.teleport(Constants::teleport1);

    if (keys[SDL_SCANCODE_5]) this->player.teleport(Constants::teleport2);
}

void Game::draw() {
    std::stack<glm::mat4> mvStack;
    // clear the screen
    glEnable(GL_CULL_FACE);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 projection = glm::perspective(float(60.0f * Constants::degreeToRadian),
                                  float(this->mainWindowWidth) / float(this->mainWindowHeight),
                                  1.0f, 150.0f);

    mvStack.push(player.getCameraDirection());

    // Skybox as single cube using cube map
//    this->skyboxShader.use();
//    this->skyboxShader.setUniformMatrix4fv("projection", glm::value_ptr(projection));

    glDepthMask(GL_FALSE); // Make sure writing to update depth test is off
    auto mvRotOnlyMat3 = glm::mat3(mvStack.top());
    mvStack.push(glm::mat4(mvRotOnlyMat3));

    glCullFace(GL_FRONT); // Drawing inside of cube!
    glBindTexture(GL_TEXTURE_CUBE_MAP, skybox[0]);
    mvStack.top() = glm::scale(mvStack.top(), glm::vec3(1.5f, 1.5f, 1.5f));
//    this->skyboxShader.setUniformMatrix4fv("modelview", glm::value_ptr(mvStack.top()));
//    rt3d::drawIndexedMesh(meshObjects[0].getMeshObject(),
//                          meshObjects[0].getMeshIndexCount(), GL_TRIANGLES);
    mvStack.pop();
    glCullFace(GL_BACK); // Drawing inside of cube!


    // Back to remainder of rendering
    glDepthMask(GL_TRUE); // Make sure depth test is on

//    this->textureShader.use();
//    this->textureShader.setUniformMatrix4fv("projection", glm::value_ptr(projection));

    // Draw a cube for ground plane
//    glBindTexture(GL_TEXTURE_2D, textures[1]);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    mvStack.push(mvStack.top());
    mvStack.top() = glm::translate(mvStack.top(), glm::vec3(-10.0f, -0.1f, -10.0f));
    mvStack.top() = glm::scale(mvStack.top(), glm::vec3(20.0f, 0.1f, 20.0f));
//    this->textureShader.setUniformMatrix4fv("modelview", glm::value_ptr(mvStack.top()));
//    rt3d::drawIndexedMesh(meshObjects[0].getMeshObject(), meshObjects[0].getMeshIndexCount(), GL_TRIANGLES);
    mvStack.pop();

    // Remember to use at least one pop operation per push...
    mvStack.pop(); // initial matrix
    glDepthMask(GL_TRUE);

    SDL_GL_SwapWindow(this->mainWindow); // swap buffers
}
