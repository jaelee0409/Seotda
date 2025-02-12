#pragma once

#include <vector>
#include <string>
#include <memory>
#include <map>

#include "Card.h"

class Player {
    public:
        Player(int x, int y, int startingMoney);
        virtual ~Player() = default;

        virtual void addCardToHand(const Card& card);
        virtual void resetHand();
        void flipHand();
        bool hasHand() const;
        bool isHuman() const { return m_IsHuman; }

        bool placeBet(int amount);
        void addWinnings(int amount);
        void resetBankroll(int newAmount);

        const std::vector<Card>& getHand() const { return m_Hand; }
        SDL_Point getPosition() const { return m_Position; }
        int getBankroll() const { return m_Bankroll; }

        virtual void renderHand(SDL_Renderer* renderer);
        virtual void renderChips(SDL_Renderer* renderer) const;

        // Card* getCard(size_t index);
        // size_t getHandSize() const;

    protected:
        std::vector<Card> m_Hand;
        SDL_Point m_Position;
        std::map<int, int> m_ChipStacks;
        int m_Bankroll;
        bool m_IsHuman;
};