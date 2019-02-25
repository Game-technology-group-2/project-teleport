cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)

project(project_teleport LANGUAGES CXX)

set(srcs main.cpp
        assetsPaths.h
        Camera.cpp Camera.h
        Constants.h
        Game.cpp Game.h
        Mesh.cpp Mesh.h
        Model.cpp Model.h
        Player.cpp Player.h
        Shader.h Shader.cpp
        stb_image.h)

add_executable(project_teleport ${srcs})

#find_package(PkgConfig)
#set(OpenGL_GL_PREFERENCE GLVND)

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

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(project_teleport PRIVATE SDL2::SDL2 SDL2::SDL2main)

#find_package(SDL2_image REQUIRED)
#target_link_libraries(project_teleport ${SDL2IMAGE_LIBRARIES})

#PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
#PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
#PKG_SEARCH_MODULE(GLM REQUIRED glm)

#target_include_directories(project_teleport PRIVATE ${SDL2IMAGE_INCLUDE_DIRS})

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
