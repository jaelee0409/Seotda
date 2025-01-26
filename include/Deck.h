#pragma once

#include <vector>
#include <memory>

#include "Card.h"

class Deck {
    public:
        Deck(SDL_Renderer* renderer);

        void initializeDeck();
        void shuffle();
        std::unique_ptr<Card> deal();
        void reset();
        bool isEmpty() const;
        void printDeck() const;
        const std::vector<std::unique_ptr<Card>>& getDeck() const;

    private:
        std::vector<std::unique_ptr<Card>> m_Cards;
        std::vector<std::unique_ptr<Card>> m_FullDeck;

        SDL_Renderer* m_Renderer;
};