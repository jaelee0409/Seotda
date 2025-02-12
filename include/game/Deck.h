#pragma once

#include <vector>
#include <memory>

#include "Card.h"

class Deck {
    public:
        Deck();
        ~Deck();

        void initializeDeck();
        void render(SDL_Renderer* renderer) const;
        void shuffle();
        Card& deal();
        void reshuffle();
        bool isEmpty() const;
        void printDeck() const;

        std::vector<Card>& getCurrentDeck();
        const std::vector<Card>& getCurrentDeck() const;

    private:
        std::vector<Card> m_CurrentDeck;
        std::vector<Card> m_FullDeck;

        SDL_Renderer* m_Renderer;
};
