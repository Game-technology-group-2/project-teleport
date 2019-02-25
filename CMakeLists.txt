cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)

project(project_teleport LANGUAGES CXX)

set(srcs main.cpp
        assetsPaths.h
        Camera.cpp Camera.h
        Constants.h
        Game.cpp Game.h
        Helpers.h
        Mesh.cpp Mesh.h
        Model.cpp Model.h
        Player.cpp Player.h
        Shader.h Shader.cpp
        stb_image.h)

add_executable(project_teleport ${srcs})

find_package(assimp REQUIRED)
target_link_libraries(project_teleport PRIVATE ${ASSIMP_LIBRARIES})
target_include_directories(project_teleport PRIVATE ${ASSIMP_INCLUDE_DIR})

find_package(GLEW REQUIRED)
target_link_libraries(project_teleport PRIVATE GLEW::GLEW)

find_package(glm CONFIG)
if (NOT GLM_FOUND) # Done mostly for Ubuntu/Debian environments which do not have the right CMake module
    target_include_directories(project_teleport PRIVATE "${CMAKE_SOURCE_DIR}/libs/glm")
endif (NOT GLM_FOUND)

find_package(OpenGL REQUIRED)
target_link_libraries(project_teleport PRIVATE OpenGL::GL)

## The modern way is not yet supported by some distros apparently (Ubuntu, Debian, Travis..).
## Gotta love working with 3 years old package versions...
#### MODERN WAY (can't use it for now)
#find_package(SDL2 CONFIG REQUIRED)
#target_link_libraries(project_teleport PRIVATE SDL2::SDL2 SDL2::SDL2main)
#### "OLD" WAY (needed for "stable" distros)
find_package(PkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
target_include_directories(project_teleport PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(project_teleport PRIVATE ${SDL2_LIBRARIES})


## Copying resource files (assets, shaders) to the CMake build directory.
## This is ugly and should hopefully disappear or be changed when/if supporting
##   package/tarball creation or install option.
add_custom_command(
        TARGET project_teleport
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_CURRENT_BINARY_DIR}/assets
)

add_custom_command(
        TARGET project_teleport
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders
        ${CMAKE_CURRENT_BINARY_DIR}/shaders
)
