#pragma once

#include <vector>
#include <string>
#include <memory>
#include <map>

#include "Card.h"

class Player {
    public:
        Player();
        Player(int x, int y, int startingMoney);
        virtual ~Player() = default;

        virtual void addCardToHand(std::unique_ptr<Card> card);
        virtual void renderHand() const;
        virtual void resetHand();

        const std::pair<std::unique_ptr<Card>, std::unique_ptr<Card>>& getHand() const;
        SDL_Rect getPosition() const { return m_Position; }

        void flipHand();
        bool hasHand() const;

        const std::map<int, int>& getChipStacks() const { return m_ChipStacks; }
        void addWinnings(int amount);
        bool placeBet(int amount);
        void resetBankroll(int amount);
        void renderChips(SDL_Renderer* renderer) const;

    protected:
        std::pair<std::unique_ptr<Card>, std::unique_ptr<Card>> m_Hand;
        SDL_Rect m_Position;
        std::map<int, int> m_ChipStacks;
        int m_Bankroll;
};