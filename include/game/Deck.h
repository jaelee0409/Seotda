#pragma once

#include <vector>

#include "game/Card.h"

class Deck {
    public:
        Deck(SDL_Renderer* renderer);

        void initializeDeck();
        void shuffle();
        Card* deal();
        void reset();
        bool isEmpty() const;
        void printDeck() const;
        const std::vector<Card*>& getDeck() const;

    private:
        SDL_Renderer* renderer;
        std::vector<Card*> cards;
        std::vector<Card*> fullDeck;
};