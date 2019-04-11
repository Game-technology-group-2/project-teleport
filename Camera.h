/**
 * This file is part of Project Teleport, a game written in C++ using the SDL2
 * library and OpenGL API.
 *
 * Copyright (C) 2018 Pierre Gillet
 *
 * Copyright (C) 2018 Joey de Vries (https://twitter.com/JoeyDeVriez)
 * https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/mesh.h
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

#ifndef PROJECT_TELEPORT_CAMERA_H
#define PROJECT_TELEPORT_CAMERA_H

#include "Constants.h"
#include "GameObject.h"
//#include "PlayerPhysicsComponent.h"

#include <glm/vec3.hpp>


class Camera {
public:
    explicit Camera(float yaw, float pitch);

//    glm::vec3 getUp() const;
    float getZoom() const;
    float getYaw() const;
    float getPitch() const;
//    // Calculates the front vector from the Camera's (updated) Euler Angles
//    void updateCameraVectors(PlayerPhysicsComponent & playerPhysicsComponent);

private:
//    glm::vec3 Up;
    float Yaw;
    float Pitch;
    float MouseSensitivity {Constants::DefaultCameraValues::sensitivity};
    float Zoom {Constants::DefaultCameraValues::zoom};
};

#endif //PROJECT_TELEPORT_CAMERA_H
