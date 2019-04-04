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

#include "Graphics.h"

#include "assetsPaths.h"
#include "Model.h"
#include "Shader.h"


Graphics::Graphics(unsigned int mainWindowWidth, unsigned int mainWindowHeight)
        : mainWindowWidth(mainWindowWidth), mainWindowHeight(mainWindowHeight) {
    setupRenderingContext();
    initializeGlew();
    loadShaders();
    loadModels();

    glEnable(GL_DEPTH_TEST);
}

Graphics::~Graphics() {
    SDL_GL_DeleteContext(mainContext);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();
}

void Graphics::loadModels() {
//    loadCubeMap(assetsPaths::skyboxTextures, this->skybox);
//
//    textures = {loadTexture(assetsPaths::concreteTexture),
//                loadTexture(assetsPaths::carpetTexture),};

//    meshObjects = {Mesh(assetsPaths::cubeObject),};

    this->models = {Model(assetsPaths::cubeModel),
                    Model(assetsPaths::deskModel),
                    Model(assetsPaths::nanosuitModel)};
}

void Graphics::draw(GameObject & gameObject) {

}

void Graphics::renderFrame() {
    SDL_GL_SwapWindow(mainWindow); // swap buffers
}

void Graphics::handleWindowEvent(const SDL_WindowEvent & windowEvent) {
    if (SDL_WINDOWEVENT_SIZE_CHANGED == windowEvent.event) {
        this->mainWindowWidth = (unsigned int) windowEvent.data1;
        this->mainWindowHeight = (unsigned int) windowEvent.data2;
        glViewport(0, 0, this->mainWindowWidth, this->mainWindowHeight);
    }
}

void Graphics::initializeGlew() {
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

void Graphics::setupRenderingContext() {
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

void Graphics::loadShaders() {
//    Shader skybox = Shader(assetsPaths::cubeMapShader.vertex.c_str(),
//                           assetsPaths::cubeMapShader.fragment.c_str());
//    Shader textured = Shader(assetsPaths::texturedShader.vertex.c_str(),
//                             assetsPaths::texturedShader.fragment.c_str());
//    Shader colorInterpolation = Shader(assetsPaths::colorInterpolationShader.vertex.c_str(),
//                                       assetsPaths::colorInterpolationShader.fragment.c_str());
    modelLoadingShader = std::make_shared<Shader>(assetsPaths::modelLoadingShader.vertex.c_str(),
                                                  assetsPaths::modelLoadingShader.fragment.c_str());
}
