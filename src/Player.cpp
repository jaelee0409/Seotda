#include <memory>
#include <iostream>

#include "Player.h"
#include "Config.h"

Player::Player() {

}

Player::Player(int x, int y) : m_Bankroll(10'000'000), m_Hand{nullptr, nullptr} {
    m_Position = { x, y, Config::CARD_WIDTH, Config::CARD_HEIGHT };
}
 
void Player::addCardToHand(std::unique_ptr<Card> card) {
    if (!m_Hand.first) {
        m_Hand.first = std::move(card);  // First card
    } else if (!m_Hand.second) {
        m_Hand.second = std::move(card); // Second card
    } else {
        std::cerr << "[Player::addCardToHand] Cannot add more than two cards!" << std::endl;
    }
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

int Player::getBankroll() const {
    return m_Bankroll;
}

void Player::addWinnings(int amount) {
    m_Bankroll += amount;
}

bool Player::placeBet(int amount) {
    if (amount > m_Bankroll) {
        std::cerr << "[Player::deductMoney] Not enough money!" << std::endl;
        return false;
    }
    m_Bankroll -= amount;
    std::cerr << "[DEBUG] after the bet bankroll: " << m_Bankroll << std::endl;
    return true;
}