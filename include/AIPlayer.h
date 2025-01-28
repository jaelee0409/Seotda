#pragma once

#include "Player.h"

class AIPlayer : public Player {
    public:
        // Constructor for AIPlayer (You could add extra functionality if needed)
        AIPlayer() {}

        // Render the hand of the AI player
        void renderHand() override {
            // Loop through each card in the AI player's hand and render it face-down
            for (size_t i = 0; i < hand.size(); ++i) {
                hand[i]->render();  // Cards should be face-down for the AI player
            }
        }
};
