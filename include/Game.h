#pragma once

#include <vector>
#include <memory>
#include <SDL.h>

#include "Player.h"
#include "Deck.h"
#include "GameStateManager.h"

class Game {
    public:
        Game();
        ~Game();

        static GameStateManager& getGameStateManager();

        bool initialize();
        void run();
        void cleanUp();

        void handleEvents();
        void update();
        void render();

        void startGame();
        void dealCards();
        void bettingPhase();
        void evaluateHands();
        void nextRound();

        void collectBet(Player* player, int amount);
        void resetPot();

    private:
        static GameStateManager s_GameStateManager;

        Deck m_Deck;
        std::vector<std::unique_ptr<Player>> m_Players;
        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        bool m_IsRunning;
        int m_Pot = 0;
};