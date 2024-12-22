#pragma once

#include <vector>
#include <string>

#include "Card.h"

class Player {
public:
    Player(const std::string& name, int startingMoney = 1000);
    virtual ~Player() = default;

    virtual void playTurn() = 0;

    void addCard(const Card& card);
    void removeCard(const Card& card);
    const std::vector<Card>& getHand() const;
    
    void bet(int amount);
    void call();
    void fold();
    void allIn();
    void resetBet();

    int getMoney() const;
    void setMoney(int money);
    int getCurrentBet() const;
    bool hasFolded() const;

protected:
    std::string name;
    int money;
    int currentBet;
    bool isFolded;
    std::vector<Card> hand;
};