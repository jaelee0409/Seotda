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

        void addCardToHand(const Card& card);
        void resetHand();
        void resetBet();
        void resetBankroll();
        void flipHand();
        bool hasHand() const;
        
        bool placeBet(int amount);
        void addWinnings(int amount);

        bool getIsHuman() const;
        bool getIsFolded() const;
        bool getIsAllIn() const;
        const std::vector<Card>& getHand() const;
        SDL_Point getPosition() const;
        int getBankroll() const;
        int getCurrentBet() const;
        const std::string& getName() const;

        void setBankroll(int amount);
        void setIsFolded(bool b);

        virtual void renderHand(SDL_Renderer* renderer);

        // Card* getCard(size_t index);
        // size_t getHandSize() const;

    protected:
        std::vector<Card> m_Hand;
        SDL_Point m_Position;
        //std::map<int, int> m_ChipStacks;
        int m_Bankroll;
        int m_CurrentBet{0};
        bool m_IsHuman;
        bool m_IsFolded{false};
        bool m_IsAllIn{false};
        std::string m_Name;
};