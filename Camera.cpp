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

#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>


Camera::Camera(glm::vec3 up, float yaw, float pitch)
        : Up(up),
          Yaw(yaw),
          Pitch(pitch) {
//    updateCameraVectors();
}

void Camera::updateCameraVectors(PlayerPhysicsComponent & playerPhysicsComponent) {
    // Calculate the new front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    glm::vec3 normalizedFront {glm::normalize(front)};
    // Normalize the vectors, because their length gets closer to 0
    // the more you look up or down which results in slower movement.
    playerPhysicsComponent.setFront(normalizedFront);
    glm::vec3 worldUp {playerPhysicsComponent.getWorldUp()};
    glm::vec3 normalizedRight = glm::normalize(glm::cross(normalizedFront, worldUp));
    playerPhysicsComponent.setRight(normalizedRight);
    Up = glm::normalize(glm::cross(normalizedRight, normalizedFront));
}

glm::vec3 Camera::getUp() const {
    return Up;
}

float Camera::getZoom() const {
    return Zoom;
}

float Camera::getYaw() const {
    return Yaw;
}

float Camera::getPitch() const {
    return Pitch;
}
