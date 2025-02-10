#pragma once

#include <vector>
#include <string>
#include <memory>

#include "Card.h"

class Player {
    public:
        Player();
        Player(int x, int y);
        virtual ~Player() = default;

        virtual void addCardToHand(std::unique_ptr<Card> card);
        virtual void renderHand() const;
        virtual void resetHand();

        const std::pair<std::unique_ptr<Card>, std::unique_ptr<Card>>& getHand() const;
        SDL_Rect getPosition() const { return m_Position; }

        void flipHand();
        bool hasHand() const;

        int getBankroll() const;
        void addWinnings(int amount);
        bool placeBet(int amount);

    protected:
        std::pair<std::unique_ptr<Card>, std::unique_ptr<Card>> m_Hand;
        SDL_Rect m_Position;
        int m_Bankroll;
};