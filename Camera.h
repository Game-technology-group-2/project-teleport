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

#ifndef PROJECT_TELEPORT_CAMERA_H
#define PROJECT_TELEPORT_CAMERA_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>

#include "Constants.h"

// Defines several possible options for camera movement.
// Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// An abstract camera class that processes input and calculates
// the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera {
public:
    // Camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // Euler Angles
    float Yaw;
    float Pitch;
    // Camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // Constructor with vectors
    explicit Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
                    float yaw = Constants::DefaultCameraValues::yaw,
                    float pitch = Constants::DefaultCameraValues::pitch);

    // Constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ,
           float yaw, float pitch);

    // Returns the view matrix calculated using Euler Angles
    // and the LookAt Matrix
    glm::mat4 GetViewMatrix();

    // Processes input received from any keyboard-like input system.
    // Accepts input parameter in the form of camera
    // defined ENUM (to abstract it from windowing systems)
    void move(Camera_Movement direction, float deltaTime);

    // Processes input received from a mouse input system.
    // Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset,
                              GLboolean constrainPitch = true);

    // Processes input received from a mouse scroll-wheel event.
    // Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset);

private:
    // Calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();
};

#endif //PROJECT_TELEPORT_CAMERA_H
