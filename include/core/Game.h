#pragma once

#include <vector>
#include <memory>
#include <SDL.h>

#include "UIManager.h"
#include "CardTextureManager.h"
#include "FontManager.h"
#include "../game/Player.h"
#include "../game/Deck.h"
#include "../game/Chip.h"

class Game {
    public:
        Game();
        ~Game();

        bool initialize();
        void run();
        void handleEvents();
        void update();
        void render();
        void cleanUp();

    private:
        SDL_Window* m_Window{nullptr};
        SDL_Renderer* m_Renderer{nullptr};
        bool m_IsRunning{false};
        
        std::unique_ptr<UIManager> m_UIManager;
        std::unique_ptr<CardTextureManager> m_CardTextureManager;
        std::unique_ptr<FontManager> m_FontManager;
};