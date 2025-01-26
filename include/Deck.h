#pragma once

#include <vector>
#include <memory>

#include "Card.h"

class Deck {
    public:
        Deck(SDL_Renderer* renderer);
        ~Deck();

        void initializeDeck(SDL_Renderer* renderer);
        void shuffle();
        Card deal();
        void reset();
        bool isEmpty() const;
        void printDeck() const;
        const std::vector<Card>& getDeck() const;
        void animateDealCard(Card& card, const SDL_Rect& dest, float speed);

    private:
        std::vector<Card> m_Cards;
        std::vector<Card> m_FullDeck;

        SDL_Renderer* m_Renderer;
};