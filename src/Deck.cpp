#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <memory>
#include <SDL_image.h>

#include "Deck.h"
#include "Card.h"

Deck::Deck() : m_Renderer(nullptr) {
    std::cerr << "[DEBUG] Deck created at: " << this << std::endl;
}

Deck::~Deck() {
    std::cerr << "[DEBUG] Deck destroyed at: " << this << std::endl;
    m_Renderer = nullptr;
}

void Deck::initializeDeck(SDL_Renderer* renderer) {
    // This is here and not in the constructor because it has to be after the SDL_CreateRenderer() function call
    m_Renderer = renderer;

    m_FullDeck.emplace_back(std::make_unique<Card>(CardID::JanuaryBright, CardSuit::January, CardType::Bright, m_Renderer));
    m_FullDeck.emplace_back(std::make_unique<Card>(CardID::JanuaryRibbon, CardSuit::January, CardType::Ribbon, m_Renderer));
    m_FullDeck.emplace_back(std::make_unique<Card>(CardID::FebruaryAnimal, CardSuit::February, CardType::Animal, m_Renderer));
    m_FullDeck.emplace_back(std::make_unique<Card>(CardID::FebruaryRibbon, CardSuit::February, CardType::Ribbon, m_Renderer));
    m_FullDeck.emplace_back(std::make_unique<Card>(CardID::MarchBright, CardSuit::March, CardType::Bright, m_Renderer));
    m_FullDeck.emplace_back(std::make_unique<Card>(CardID::MarchRibbon, CardSuit::March, CardType::Ribbon, m_Renderer));
    m_FullDeck.emplace_back(std::make_unique<Card>(CardID::AprilAnimal, CardSuit::April, CardType::Animal, m_Renderer));
    m_FullDeck.emplace_back(std::make_unique<Card>(CardID::AprilRibbon, CardSuit::April, CardType::Ribbon, m_Renderer));
    m_FullDeck.emplace_back(std::make_unique<Card>(CardID::MayRibbon, CardSuit::May, CardType::Ribbon, m_Renderer));
    m_FullDeck.emplace_back(std::make_unique<Card>(CardID::MayDoubleJunk, CardSuit::May, CardType::DoubleJunk, m_Renderer));
    m_FullDeck.emplace_back(std::make_unique<Card>(CardID::JuneAnimal, CardSuit::June, CardType::Animal, m_Renderer));
    m_FullDeck.emplace_back(std::make_unique<Card>(CardID::JuneRibbon, CardSuit::June, CardType::Ribbon, m_Renderer));
    m_FullDeck.emplace_back(std::make_unique<Card>(CardID::JulyAnimal, CardSuit::July, CardType::Animal, m_Renderer));
    m_FullDeck.emplace_back(std::make_unique<Card>(CardID::JulyRibbon, CardSuit::July, CardType::Ribbon, m_Renderer));
    m_FullDeck.emplace_back(std::make_unique<Card>(CardID::AugustBright, CardSuit::August, CardType::Bright, m_Renderer));
    m_FullDeck.emplace_back(std::make_unique<Card>(CardID::AugustAnimal, CardSuit::August, CardType::Animal, m_Renderer));
    m_FullDeck.emplace_back(std::make_unique<Card>(CardID::SeptemberRibbon, CardSuit::September, CardType::Ribbon, m_Renderer));
    m_FullDeck.emplace_back(std::make_unique<Card>(CardID::SeptemberDoubleJunk, CardSuit::September, CardType::DoubleJunk, m_Renderer));
    m_FullDeck.emplace_back(std::make_unique<Card>(CardID::OctoberAnimal, CardSuit::October, CardType::Animal, m_Renderer));
    m_FullDeck.emplace_back(std::make_unique<Card>(CardID::OctoberRibbon, CardSuit::October, CardType::Ribbon, m_Renderer));

    reshuffle();
}

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(m_CurrentDeck.begin(), m_CurrentDeck.end(), g);
}

std::unique_ptr<Card> Deck::deal() {
    if (m_CurrentDeck.empty()) {
        std::cerr << "[Deck::deal] No more cards in the deck!" << std::endl;
        return nullptr;
    }

    // Deal the top card (remove from the deck)
    std::unique_ptr<Card> dealtCard = std::move(m_CurrentDeck.back());
    m_CurrentDeck.pop_back();
    return dealtCard;
}

void Deck::reshuffle() {
    std::cerr << "[DEBUG] Reshuffling deck at: " << this << std::endl;
    std::cerr << "[DEBUG] Clearing current deck..." << std::endl;
    m_CurrentDeck.clear();
    for (const auto& card : m_FullDeck) {
        m_CurrentDeck.emplace_back(std::make_unique<Card>(card->getCardID(), card->getSuit(), card->getType(), m_Renderer));
    }
    std::cerr << "[DEBUG] Shuffling deck..." << std::endl;
    shuffle();
    std::cerr << "[DEBUG] Deck reshuffled successfully. 2" << std::endl;
    for (size_t i = 0; i < m_CurrentDeck.size(); ++i) {
        m_CurrentDeck[i]->setPosition(m_CurrentDeck[i]->getPositionX() + i, m_CurrentDeck[i]->getPositionY() - i);
    }
}

bool Deck::isEmpty() const {
    return m_CurrentDeck.empty();
}

void Deck::printDeck() const {
    for (const auto& card : m_CurrentDeck) {
        card->printCard();
    }
}

const std::vector<std::unique_ptr<Card>>& Deck::getDeck() const {
    return m_CurrentDeck;
}
