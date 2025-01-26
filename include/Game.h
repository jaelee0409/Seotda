#pragma once

#include <vector>
#include <memory>

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
        bool loadFaceDownTexture();

        void startGame();
        void endGame();
        void playRound();
        void dealCard();
        void bettingRound();

    private:
        static GameStateManager s_GameStateManager;

        std::vector<Player*> m_Players;  // Vector of players (1 human, 4 AI)
        Deck m_Deck;  // The card deck used in the game
        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        bool m_IsRunning;
        
        int m_Pot;  // The total money pot for the current round
        int m_CurrentBet;  // The current bet across all players
        std::vector<Card> m_PlayerHand;
};