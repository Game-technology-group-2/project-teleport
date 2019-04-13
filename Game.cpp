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

#include "Constants.h"
#include "DemoWorld.h"

#include <memory>
#include <SDL2/SDL.h>


Game::Game() {
    world = std::make_unique<DemoWorld>();
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
                    world->getGraphics()->handleWindowEvent(sdlEvent.window);
                    break;

                default:
                    break;
            }
        }

        world->update();

        // Wait a bit if rendering too fast
        auto currentTime {SDL_GetTicks()};
        auto maximumTime {startTime + Constants::MS_PER_FRAME};
        // Only wait if going faster than the expected update rate
        if (currentTime < maximumTime) {
            SDL_Delay(maximumTime - currentTime);
        }
    }
}
