#pragma once

#include <vector>
#include <memory>

#include "Card.h"

class Deck {
    public:
        Deck(SDL_Renderer* renderer);
        ~Deck();

        static bool loadFaceDownTexture(SDL_Renderer* renderer);
        static SDL_Texture* getFaceDownTexture();
        static void setFaceDownTexture(SDL_Texture* texture);
        static void destroyFaceDownTexture();

        void initializeDeck(SDL_Renderer* renderer);
        void shuffle();
        Card deal();
        void reset();
        bool isEmpty() const;
        void printDeck() const;
        const std::vector<Card>& getDeck() const;
        void animateDealCard(Card& card, const SDL_Rect& dest, float speed);

    private:
        static SDL_Texture* s_FaceDownTexture;
        std::vector<Card> m_CurrentDeck;
        std::vector<Card> m_FullDeck;

        SDL_Renderer* m_Renderer;
};