#pragma once

#include <vector>
#include <string>

#include "Card.h"

class Player {
    public:
        // Virtual destructor to ensure proper cleanup when deleting derived classes
        virtual ~Player() {}

        // Add a card to the player's hand
        virtual void addCardToHand(Card* card) {
            hand.push_back(card);
        }

        // Abstract method that must be implemented by the derived classes to render the player's hand
        virtual void renderHand() = 0;

        // You can also include a method to get the number of cards for each player, if needed
        size_t getHandSize() const {
            return hand.size();
        }

        // Optionally, a method to flip a card for testing purposes
        void flipCardInHand(int index) {
            if (index >= 0 && index < hand.size()) {
                hand[index]->flip();
            }
        }

    protected:
        std::vector<Card*> hand;  // Cards in the player's hand
};