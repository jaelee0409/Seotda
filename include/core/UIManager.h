#pragma once

#include <SDL2/SDL.h>
#include <memory>

#include "../screens/Screen.h"

class UIManager {
    public:
        UIManager(SDL_Renderer* renderer);
        ~UIManager();

        static UIManager* getInstance();
    
        void setScreen(std::unique_ptr<Screen> newScreen);
        void handleEvent(SDL_Event& event);
        void update();
        void render();

    private:
        std::unique_ptr<Screen> currentScreen;
        static UIManager* s_Instance;
        SDL_Renderer* m_Renderer;
};
