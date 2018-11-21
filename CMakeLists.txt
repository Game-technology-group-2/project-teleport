cmake_minimum_required(VERSION 3.9.2)
set(CMAKE_CXX_STANDARD 17)

project(project_teleport)
set(srcs main.cpp
        assetsLoader.cpp assetsLoader.h
        assetsPaths.h
        constants.h
        Mesh.cpp Mesh.h
        Game.cpp Game.h
        md2model.cpp md2model.h
        Player.cpp Player.h
        rt3d.cpp rt3d.h
        rt3dObjLoader.cpp rt3dObjLoader.h
        Shader.h Shader.cpp)
add_executable(project_teleport ${srcs})

find_package(PkgConfig)
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(GLM REQUIRED glm)

target_link_libraries(
        project_teleport
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${SDL2_LIBRARIES}
        ${SDL2IMAGE_LIBRARIES}
)

target_include_directories(
        project_teleport PRIVATE
        ${OPENGL_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIRS}
        ${GLM_INCLUDE_DIRS}
        ${SDL2_INCLUDE_DIRS}
        ${SDL2IMAGE_INCLUDE_DIRS}
)
