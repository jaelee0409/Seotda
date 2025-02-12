#include <memory>
#include <iostream>

#include "core/Config.h"
#include "game/Player.h"
#include "game/Chip.h"

Player::Player(int x, int y, int startingMoney) : m_Bankroll(startingMoney) {
    m_Position = { x, y };
    resetBankroll(startingMoney);
}
 
void Player::addCardToHand(const Card& card) {
    m_Hand.push_back(card);
}

void Player::renderHand(SDL_Renderer* renderer) {
    int offset = 0;
    for (auto& card : m_Hand) {
        card.setPosition(m_Position.x + offset, m_Position.y);
        card.render(renderer);
        offset += 60;
        // if (card) {
        //     card->setPosition(m_Position.x + offset, m_Position.y);
        //     card->render(renderer);
        //     offset += 60;
        // }
    }
}

void Player::resetHand() {
    m_Hand.clear();
}

void Player::flipHand() {
    for (auto& card : m_Hand) {
        card.flip();
    }
}

bool Player::hasHand() const {
    return !m_Hand.empty();
}

void Player::addWinnings(int amount) {
    m_Bankroll += amount;
    resetBankroll(m_Bankroll);
}

bool Player::placeBet(int amount) {
    if (amount > m_Bankroll) {
        std::cerr << "[Player::placeBet] Not enough chips for bet of " << amount << "!" << std::endl;
        return false;
    }

    m_Bankroll -= amount;  // ✅ Deduct from bankroll immediately

    std::vector<int> chipValues = { 1000000, 500000, 100000, 50000, 10000 };

    for (int chip : chipValues) {
        while (amount >= chip && m_ChipStacks[chip] > 0) {
            m_ChipStacks[chip]--;
            amount -= chip;
        }
    }

    return true;
}
void Player::resetBankroll(int amount) {
    m_ChipStacks.clear();  // ✅ Clear old chip data

    std::vector<int> chipValues = { 1000000, 500000, 100000, 50000, 10000 };
    
    for (int chip : chipValues) {
        while (amount >= chip) {
            m_ChipStacks[chip]++;
            amount -= chip;
        }
    }
}

void Player::renderChips(SDL_Renderer* renderer) const {
    // int x = m_Position.x + 150;  // Offset from player
    // int y = m_Position.y;

    // for (const auto& [chipValue, count] : m_ChipStacks) {
    //     for (int i = 0; i < count; ++i) {
    //         if (i >= 10)
    //             break;
    //         SDL_Rect chipRect = { x, y - (i * 5), 40, 40 };
    //         SDL_RenderCopy(renderer, Chip::getTextureForValue(chipValue), nullptr, &chipRect);
    //     }
    //     x += 40;
    // }
}