#pragma once

#include "Player.h"

class AIPlayer : public Player {
    public:
        AIPlayer(const std::string& name, int startingMoney = 1000);
        ~AIPlayer();

        void playTurn() override;

    private:
        void makeDecision();
};