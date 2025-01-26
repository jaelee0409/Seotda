#pragma once

#include <vector>
#include <memory>

#include "Player.h"
#include "Deck.h"
#include "GameStateManager.h"

enum class GameStateEnum {
    Intro,
    Menu,
    Rules,
    Gameplay
};

class Game {
    public:
        Game();
        ~Game();

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
        void dealCards();  // Distribute cards to players
        GameStateEnum getCurrentGameState() const;
        void setGameState(GameStateEnum state);
        void bettingRound();  // Manage the betting round (bet, call, all-in, fold)

    private:
        bool m_IsRunning;
        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;

        GameStateEnum m_CurrentGameState;
        GameStateManager m_StateManager;
        std::vector<Player*> m_Players;  // Vector of players (1 human, 4 AI)
        std::unique_ptr<Deck> m_Deck;  // The card deck used in the game
        int m_Pot;  // The total money pot for the current round
        int m_CurrentBet;  // The current bet across all players
};