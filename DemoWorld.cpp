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

#include "DemoWorld.h"

#include "assetsPaths.h"
#include "Constants.h"
#include "Model.h"
#include "PlayerGraphicsComponent.h"
#include "PlayerInputComponent.h"
#include "PlayerPhysicsComponent.h"
#include "TurretGraphicsComponent.h"
#include "TurretInputComponent.h"
#include "TurretPhysicsComponent.h"


DemoWorld::DemoWorld() {
    auto playerPhysics {std::make_shared<PlayerPhysicsComponent>(Constants::DefaultCameraValues::speed,
                                                                 Constants::DefaultCameraValues::sensitivity,
                                                                 Constants::DefaultCameraValues::worldUp,
                                                                 Constants::DefaultCameraValues::yaw,
                                                                 Constants::DefaultCameraValues::pitch)};

    player = std::make_shared<GameObject>(std::make_shared<PlayerInputComponent>(),
                                          playerPhysics,
                                          std::make_shared<PlayerGraphicsComponent>(),
                                          Constants::spawnPosition);

    graphics = std::make_shared<Graphics>(Constants::BaseWindowSize::width,
                                          Constants::BaseWindowSize::height,
                                          Constants::DefaultCameraValues::zoom,
                                          player, playerPhysics);

    auto turretModel {std::make_shared<Model>(Model(assetsPaths::nanosuitModel))};

    GameObject turret {std::make_shared<TurretInputComponent>(),
                       std::make_shared<TurretPhysicsComponent>(Constants::DefaultCameraValues::worldUp, 0, 0),
                       std::make_shared<TurretGraphicsComponent>(turretModel),
                       Constants::spawnPosition};

    worldObjects.push_back(turret);
}

void DemoWorld::update() {
    player->update(*graphics);

    for (GameObject object : worldObjects) {
        object.update(*graphics);
    }

    graphics->renderFrame();
}

const std::shared_ptr<Graphics> & DemoWorld::getGraphics() const {
    return graphics;
}
