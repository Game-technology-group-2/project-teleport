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

#include "PlayerInputComponent.h"

#include <GL/glew.h>
#include <SDL_types.h>
#include <SDL_scancode.h>
#include <SDL_keyboard.h>
#include <SDL_mouse.h>

#include "Helpers.h"


void PlayerInputComponent::update(GameObject & gameObject) {
    Helpers::Direction direction = gameObject.getDirection();
    const Uint8 *keys = SDL_GetKeyboardState(nullptr);
    bool forward {false};
    bool backward {false};
    bool left {false};
    bool right {false};

    if (keys[SDL_SCANCODE_W] && !keys[SDL_SCANCODE_S]) {
        forward = true;
    } else if (keys[SDL_SCANCODE_S] && !keys[SDL_SCANCODE_W]) {
        backward = true;
    }

    if (keys[SDL_SCANCODE_A] && !keys[SDL_SCANCODE_D]) {
        left = true;
    } else if (keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_A]) {
        right = true;
    }

    if (forward) {
        if (right) {
            direction = Helpers::Direction::FORWARD_RIGHT;
        } else if (left) {
            direction = Helpers::Direction::FORWARD_LEFT;
        }
    } else if (backward) {
        if (right) {
            direction = Helpers::Direction::BACKWARD_RIGHT;
        } else if (left) {
            direction = Helpers::Direction::BACKWARD_LEFT;
        }
    }

    gameObject.setDirection(direction);

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
//    this->player.processMouseMovement(x, y, true);
}
