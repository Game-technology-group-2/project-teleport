#ifndef PROJECT_TELEPORT_GAME_H
#define PROJECT_TELEPORT_GAME_H

#include <GL/glew.h>
#include <vector>
#ifdef _WIN32
#include <SDL.h>
#endif
#ifndef _WIN32
#include <SDL2/SDL.h>
#endif

#include "Mesh.h"
#include "Player.h"


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
    GLuint skyboxShader;
    GLuint textureShader;
    std::vector<Mesh> meshObjects;
    std::vector<GLuint> textures;
    std::vector<GLuint> skybox = std::vector<GLuint>(6);
    Player player = Player(glm::vec3(-2.0f, 1.0f, 8.0f),
                           glm::vec3(0.0f, 1.0f, -1.0f),
                           glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);

    void initializeGlew();
    void setupRenderingContext();
    void init();
    void loadShaders();
    void handleWindowEvent(const SDL_WindowEvent & windowEvent);
    void handleUserInput();
    void draw();
};


#endif // PROJECT_TELEPORT_GAME_H