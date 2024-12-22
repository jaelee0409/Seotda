#pragma once

#include <SDL.h>

class Game {
public:
    Game();
    ~Game();

    bool initialize();
    void run();
    void cleanUp();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;

    void handleEvents();
    void update();
    void render();
};
