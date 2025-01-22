#pragma once

#include <vector>
#include <memory>

#include "Player.h"
#include "Deck.h"

enum class GameState {
    WaitingForInput,
    PlayerTurn,
    RoundEnded,
    GameOver
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

        void startGame();
        void endGame();
        void playRound();
        void dealCards();  // Distribute cards to players
        void updateGameState();
        void bettingRound();  // Manage the betting round (bet, call, all-in, fold)

    private:
        bool isRunning;
        SDL_Window* window;
        SDL_Renderer* renderer;

        GameState currentState;
        std::vector<Player*> players;  // Vector of players (1 human, 4 AI)
        std::unique_ptr<Deck> deck;  // The card deck used in the game
        int pot;  // The total money pot for the current round
        int currentBet;  // The current bet across all players
};