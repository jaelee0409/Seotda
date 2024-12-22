#pragma once

#include <vector>

#include "Card.h"

class Deck {
    public:
        Deck();

        void shuffle();
        Card deal();
        void reset();
        bool isEmpty() const;

    private:
        std::vector<Card> cards;
        std::vector<int> cardIndices;
        void populateDeck();
};