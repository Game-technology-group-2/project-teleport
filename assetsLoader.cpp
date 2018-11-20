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

#include "assetsLoader.h"

#include <iostream>
#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#endif
#ifndef _WIN32
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif

#include <string>


// A simple texture loading function
// lots of room for improvement - and better error checking!
GLuint loadTexture(const std::string fileName) {
    GLuint texID;
    glGenTextures(1, &texID); // generate texture ID

    SDL_Surface *tmpSurface = IMG_Load(fileName.c_str());
    if (nullptr == tmpSurface) {
        throw std::runtime_error("Error loading the " + std::string(fileName) + " image : " + IMG_GetError());
    }

    // bind texture and set parameters
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    SDL_PixelFormat *format = tmpSurface->format;

    GLuint externalFormat, internalFormat;
    if (format->Amask) {
        internalFormat = GL_RGBA;
        externalFormat = (format->Rmask < format->Bmask) ? GL_RGBA : GL_BGRA;
    } else {
        internalFormat = GL_RGB;
        externalFormat = (format->Rmask < format->Bmask) ? GL_RGB : GL_BGR;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, tmpSurface->w, tmpSurface->h, 0,
                 externalFormat, GL_UNSIGNED_BYTE, tmpSurface->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    SDL_FreeSurface(tmpSurface); // texture loaded, free the temporary buffer
    return texID;	// return value of texture ID
}


// A simple cubemap loading function
// lots of room for improvement - and better error checking!
void loadCubeMap(const std::vector<std::string> & fileName, std::vector<GLuint> & texID) {
    glGenTextures(1, &texID[0]); // generate texture ID
    GLenum sides[6] = { GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
                        GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
                        GL_TEXTURE_CUBE_MAP_POSITIVE_X,
                        GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
                        GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
                        GL_TEXTURE_CUBE_MAP_NEGATIVE_Y };

    glBindTexture(GL_TEXTURE_CUBE_MAP, texID[0]); // bind texture and set parameters
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    for(size_t i = 0; i != fileName.size(); ++i) {
        SDL_Surface *tmpSurface = IMG_Load(fileName[i].c_str());
        if (nullptr == tmpSurface) {
            std::cout << "Error loading bitmap" << std::endl;
            throw std::runtime_error("Error loading the " + std::string(fileName[i]) + " image : " + IMG_GetError());
        }

        // skybox textures should not have alpha (assuming this is true!)
        SDL_PixelFormat *format = tmpSurface->format;
        GLuint externalFormat = (format->Rmask < format->Bmask) ? GL_RGB : GL_BGR;

        glTexImage2D(sides[i], 0, GL_RGB, tmpSurface->w, tmpSurface->h, 0,
                     externalFormat, GL_UNSIGNED_BYTE, tmpSurface->pixels);
        // texture loaded, free the temporary buffer
        SDL_FreeSurface(tmpSurface);
    }
}
