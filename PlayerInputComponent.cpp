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

#include <SDL_types.h>
#include <SDL_scancode.h>
#include <SDL_keyboard.h>
#include <SDL_opengl.h>
#include <SDL_mouse.h>
#include "PlayerInputComponent.h"
#include "Helpers.h"


void PlayerInputComponent::update(GameObject & gameObject) {
    const Uint8 *keys = SDL_GetKeyboardState(nullptr);
    if (keys[SDL_SCANCODE_W]) {
        gameObject.setDirection(Helpers::Movement::FORWARD);
    }

//        GameObject.move(Helpers::Movement::FORWARD, 0.1f);
//    if (keys[SDL_SCANCODE_S]) (Helpers::Movement::BACKWARD, 0.1f);
//    if (keys[SDL_SCANCODE_A]) player.move(Helpers::Movement::LEFT, 0.1f);
//    if (keys[SDL_SCANCODE_D]) player.move(Helpers::Movement::RIGHT, 0.1f);

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
