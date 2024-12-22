#pragma once

#include <SDL.h>

#include "Player.h"

class HumanPlayer : public Player {
    public:
        HumanPlayer(const std::string& name, int startingMoney = 1000);
        ~HumanPlayer();

        void playTurn() override;
        void handleEvent(const SDL_Event& event);  // Handle player input (bet, call, fold, etc.)
};