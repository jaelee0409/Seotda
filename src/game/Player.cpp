#include <memory>
#include <iostream>

#include "core/Config.h"
#include "game/Player.h"
#include "game/Chip.h"

Player::Player(int x, int y, int startingMoney) : m_Bankroll(startingMoney) {
    m_Position = { x, y };
    setBankroll(startingMoney);
    resetBet();
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
    }
}

void Player::resetHand() {
    m_Hand.clear();
}

void Player::resetBet() {
    m_CurrentBet = 0;
}

void Player::resetBankroll() {
    m_Bankroll = 0;
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
}

bool Player::placeBet(int amount) {
    if (amount > m_Bankroll) {
        std::cerr << "[ERROR] Not enough chips for bet of " << amount << "\n";
        return false;
    }

    m_Bankroll -= amount;
    m_CurrentBet += amount;

    return true;
}

/*
  ==============================================================================
    Getters
  ==============================================================================
*/
bool Player::getIsHuman() const {
    return m_IsHuman;
}

bool Player::getIsFolded() const {
    return m_IsFolded;
}

bool Player::getIsAllIn() const {
    return m_IsAllIn;
}

const std::vector<Card>& Player::getHand() const {
    return m_Hand;
}

SDL_Point Player::getPosition() const {
    return m_Position;
}

int Player::getBankroll() const {
    return m_Bankroll;
}

int Player::getCurrentBet() const {
    return m_CurrentBet;
}

const std::string& Player::getName() const {
    return m_Name;
}

/*
  ==============================================================================
    Setters
  ==============================================================================
*/
void Player::setBankroll(int amount) {
    m_Bankroll = amount;
}

void Player::setIsFolded(bool b) {
    m_IsFolded = b;
};