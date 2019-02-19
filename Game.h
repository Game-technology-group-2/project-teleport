#ifndef PROJECT_TELEPORT_GAME_H
#define PROJECT_TELEPORT_GAME_H

#include <GL/glew.h>
#include <memory>
#include <SDL2/SDL.h>
#include <vector>

#include "assetsPaths.h"
#include "Camera.h"
#include "Mesh.h"
#include "Model.h"
#include "Player.h"
#include "Shader.h"


class Game {
public:
    Game();
    ~Game();
    void runEventLoop();

private:
    SDL_Window *mainWindow; // window handle
    SDL_GLContext mainContext; // OpenGL context handle
    unsigned int mainWindowWidth;
    unsigned int mainWindowHeight;
//    std::shared_ptr<Shader> skyboxShader;
//    std::shared_ptr<Shader> textureShader;
//    std::shared_ptr<Shader> colorInterpolationShader;
    std::shared_ptr<Shader> modelLoadingShader;
//    std::vector<Mesh> meshObjects;
//    std::vector<GLuint> textures;
    std::vector<Model> models;
    std::vector<GLuint> skybox = std::vector<GLuint>(6);
//    Player player = Player(glm::vec3(-2.0f, 1.0f, 8.0f),
//                           glm::vec3(0.0f, 1.0f, -1.0f),
//                           glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
//    Player player = Player(glm::vec3(-2.0f, 1.0f, 8.0f),
//                           glm::vec3(0.0f, 1.0f, 0.0f),
//                           0.0f, 0.0f);
    Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));

    void initializeGlew();
    void setupRenderingContext();
    void init();
    void loadShaders();
    void handleWindowEvent(const SDL_WindowEvent & windowEvent);
    void handleUserInput();
    void draw();
};


#endif // PROJECT_TELEPORT_GAME_H
