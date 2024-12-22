#pragma once

#include <vector>

#include "game/Card.h"

class Deck {
    public:
        Deck(SDL_Renderer* renderer);

        void shuffle();
        Card deal();
        void reset();
        bool isEmpty() const;
        void printDeck() const;

    private:
        SDL_Renderer* renderer;
        std::vector<Card> cards;
        std::vector<int> cardIndices;
        void populateDeck();
};