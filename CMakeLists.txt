cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)

project(project_teleport)
set(srcs main.cpp
        assetsPaths.h
        constants.h
        Mesh.cpp Mesh.h
        Model.cpp Model.h
        Game.cpp Game.h
        Player.cpp Player.h
        Shader.h Shader.cpp
        stb_image.h Camera.cpp Camera.h)

add_executable(project_teleport ${srcs})

find_package(PkgConfig)
set(OpenGL_GL_PREFERENCE GLVND)
find_package(assimp REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

target_link_libraries(
        project_teleport
        ${ASSIMP_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${SDL2_LIBRARIES}
        ${SDL2IMAGE_LIBRARIES}
)

target_include_directories(
        project_teleport PRIVATE
        ${ASSIMP_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIRS}
        ${GLM_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIR}
        ${SDL2_INCLUDE_DIRS}
        ${SDL2IMAGE_INCLUDE_DIRS}
)
