#include <memory>
#include <iostream>

#include "Player.h"
#include "Config.h"
#include "Chip.h"

Player::Player() {

}

Player::Player(int x, int y, int startingMoney) : m_Bankroll(startingMoney), m_Hand{nullptr, nullptr} {
    m_Position = { x, y, Config::CARD_WIDTH, Config::CARD_HEIGHT };
    resetBankroll(startingMoney);
}
 
void Player::addCardToHand(std::unique_ptr<Card> card) {
    if (!card)
        return;

    if (!m_Hand.first) {
        m_Hand.first = std::move(card);
        return;
    }
    
    if (!m_Hand.second) {
        m_Hand.second = std::move(card);
        return;
    }

    std::cerr << "[Player::addCardToHand] Cannot add more than two cards!" << std::endl;
}

const std::pair<std::unique_ptr<Card>, std::unique_ptr<Card>>& Player::getHand() const {
    return m_Hand;
}

void Player::renderHand() const {
    if(m_Hand.first)
        m_Hand.first->render();
    if(m_Hand.second)
        m_Hand.second->render();
}

void Player::resetHand() {
    std::cerr << "[DEBUG] Resetting player's hand..." << std::endl;
    m_Hand.first.reset();
    m_Hand.second.reset();
    
}

void Player::flipHand() {
    if (m_Hand.first) {
        m_Hand.first->flip();
    }
    if (m_Hand.second) {
        m_Hand.second->flip();
    }
}

bool Player::hasHand() const {
    return m_Hand.first != nullptr || m_Hand.second != nullptr;
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
    int x = m_Position.x + 150;  // Offset from player
    int y = m_Position.y;

    for (const auto& [chipValue, count] : m_ChipStacks) {
        for (int i = 0; i < count; ++i) {
            if (i >= 10)
                break;
            SDL_Rect chipRect = { x, y - (i * 5), 40, 40 };
            SDL_RenderCopy(renderer, Chip::getTextureForValue(chipValue), nullptr, &chipRect);
        }
        x += 40;
    }
}