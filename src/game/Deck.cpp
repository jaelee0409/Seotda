#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <memory>

#include "Deck.h"
#include "Card.h"

Deck::Deck(SDL_Renderer* renderer) : m_Renderer(renderer) {
    initializeDeck();
}

void Deck::initializeDeck() {
    m_FullDeck.push_back(std::make_unique<Card>(CardID::JanuaryBright, CardSuit::January, CardType::Bright, m_Renderer));
    m_FullDeck.push_back(std::make_unique<Card>(CardID::JanuaryRibbon, CardSuit::January, CardType::Ribbon, m_Renderer));
    m_FullDeck.push_back(std::make_unique<Card>(CardID::FebruaryAnimal, CardSuit::February, CardType::Animal, m_Renderer));
    m_FullDeck.push_back(std::make_unique<Card>(CardID::FebruaryRibbon, CardSuit::February, CardType::Ribbon, m_Renderer));
    m_FullDeck.push_back(std::make_unique<Card>(CardID::MarchBright, CardSuit::March, CardType::Bright, m_Renderer));
    m_FullDeck.push_back(std::make_unique<Card>(CardID::MarchRibbon, CardSuit::March, CardType::Ribbon, m_Renderer));
    m_FullDeck.push_back(std::make_unique<Card>(CardID::AprilAnimal, CardSuit::April, CardType::Animal, m_Renderer));
    m_FullDeck.push_back(std::make_unique<Card>(CardID::AprilRibbon, CardSuit::April, CardType::Ribbon, m_Renderer));
    m_FullDeck.push_back(std::make_unique<Card>(CardID::MayRibbon, CardSuit::May, CardType::Ribbon, m_Renderer));
    m_FullDeck.push_back(std::make_unique<Card>(CardID::MayDoubleJunk, CardSuit::May, CardType::DoubleJunk, m_Renderer));
    m_FullDeck.push_back(std::make_unique<Card>(CardID::JuneAnimal, CardSuit::June, CardType::Animal, m_Renderer));
    m_FullDeck.push_back(std::make_unique<Card>(CardID::JuneRibbon, CardSuit::June, CardType::Ribbon, m_Renderer));
    m_FullDeck.push_back(std::make_unique<Card>(CardID::JulyAnimal, CardSuit::July, CardType::Animal, m_Renderer));
    m_FullDeck.push_back(std::make_unique<Card>(CardID::JulyRibbon, CardSuit::July, CardType::Ribbon, m_Renderer));
    m_FullDeck.push_back(std::make_unique<Card>(CardID::AugustBright, CardSuit::August, CardType::Bright, m_Renderer));
    m_FullDeck.push_back(std::make_unique<Card>(CardID::AugustAnimal, CardSuit::August, CardType::Animal, m_Renderer));
    m_FullDeck.push_back(std::make_unique<Card>(CardID::SeptemberRibbon, CardSuit::September, CardType::Ribbon, m_Renderer));
    m_FullDeck.push_back(std::make_unique<Card>(CardID::SeptemberDoubleJunk, CardSuit::September, CardType::DoubleJunk, m_Renderer));
    m_FullDeck.push_back(std::make_unique<Card>(CardID::OctoberAnimal, CardSuit::October, CardType::Animal, m_Renderer));
    m_FullDeck.push_back(std::make_unique<Card>(CardID::OctoberRibbon, CardSuit::October, CardType::Ribbon, m_Renderer));

    reset();

    for (size_t i = 0; i < m_Cards.size(); ++i) {
        m_Cards[i]->setPosition(m_Cards[i]->getPositionX() + i, m_Cards[i]->getPositionY() - i);
    }
}

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(m_Cards.begin(), m_Cards.end(), g);
}

std::unique_ptr<Card> Deck::deal() {
    if (m_Cards.empty()) {
        std::cerr << "No more cards in the deck!" << std::endl;
        return nullptr;
    }
    // Deal the top card (remove from the deck)
    auto dealtCard = std::move(m_Cards.back());
    m_Cards.pop_back();
    return dealtCard;
}

void Deck::reset() {
    m_Cards.clear();
    for (auto& card : m_FullDeck) {
        m_Cards.push_back(std::make_unique<Card>(*card));
    }
    shuffle();
}

bool Deck::isEmpty() const {
    return m_Cards.empty();
}

void Deck::printDeck() const {
    for (const auto& card : m_Cards) {
        card->printCard();
    }
}

const std::vector<std::unique_ptr<Card>>& Deck::getDeck() const {
    return m_Cards;
}
