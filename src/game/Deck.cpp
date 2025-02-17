#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <memory>
#include <SDL_image.h>

#include "core/Config.h"
#include "game/Deck.h"
#include "game/Card.h"

Deck::Deck() {
    std::cerr << "[DEBUG] Deck created at: " << this << std::endl;
}

Deck::~Deck() {
    std::cerr << "[DEBUG] Deck destroyed at: " << this << std::endl;
    m_Renderer = nullptr;
}

void Deck::initializeDeck() {
    // m_FullDeck.reserve(20);
    // m_FullDeck.emplace_back(std::make_unique<Card>(CardID::JanuaryRibbon, CardSuit::January, CardType::Bright));
    // m_FullDeck.emplace_back(std::make_unique<Card>(CardID::JanuaryRibbon, CardSuit::January, CardType::Ribbon));
    // m_FullDeck.emplace_back(std::make_unique<Card>(CardID::FebruaryAnimal, CardSuit::February, CardType::Animal));
    // m_FullDeck.emplace_back(std::make_unique<Card>(CardID::FebruaryRibbon, CardSuit::February, CardType::Ribbon));
    // m_FullDeck.emplace_back(std::make_unique<Card>(CardID::MarchBright, CardSuit::March, CardType::Bright));
    // m_FullDeck.emplace_back(std::make_unique<Card>(CardID::MarchRibbon, CardSuit::March, CardType::Ribbon));
    // m_FullDeck.emplace_back(std::make_unique<Card>(CardID::AprilAnimal, CardSuit::April, CardType::Animal));
    // m_FullDeck.emplace_back(std::make_unique<Card>(CardID::AprilRibbon, CardSuit::April, CardType::Ribbon));
    // m_FullDeck.emplace_back(std::make_unique<Card>(CardID::MayRibbon, CardSuit::May, CardType::Ribbon));
    // m_FullDeck.emplace_back(std::make_unique<Card>(CardID::MayDoubleJunk, CardSuit::May, CardType::DoubleJunk));
    // m_FullDeck.emplace_back(std::make_unique<Card>(CardID::JuneAnimal, CardSuit::June, CardType::Animal));
    // m_FullDeck.emplace_back(std::make_unique<Card>(CardID::JuneRibbon, CardSuit::June, CardType::Ribbon));
    // m_FullDeck.emplace_back(std::make_unique<Card>(CardID::JulyAnimal, CardSuit::July, CardType::Animal));
    // m_FullDeck.emplace_back(std::make_unique<Card>(CardID::JulyRibbon, CardSuit::July, CardType::Ribbon));
    // m_FullDeck.emplace_back(std::make_unique<Card>(CardID::AugustBright, CardSuit::August, CardType::Bright));
    // m_FullDeck.emplace_back(std::make_unique<Card>(CardID::AugustAnimal, CardSuit::August, CardType::Animal));
    // m_FullDeck.emplace_back(std::make_unique<Card>(CardID::SeptemberRibbon, CardSuit::September, CardType::Ribbon));
    // m_FullDeck.emplace_back(std::make_unique<Card>(CardID::SeptemberDoubleJunk, CardSuit::September, CardType::DoubleJunk));
    // m_FullDeck.emplace_back(std::make_unique<Card>(CardID::OctoberAnimal, CardSuit::October, CardType::Animal));
    // m_FullDeck.emplace_back(std::make_unique<Card>(CardID::OctoberRibbon, CardSuit::October, CardType::Ribbon));

    m_FullDeck.reserve(20);
    m_FullDeck.emplace_back(CardID::JanuaryRibbon, CardSuit::January, CardType::Bright);
    m_FullDeck.emplace_back(CardID::JanuaryRibbon, CardSuit::January, CardType::Ribbon);
    m_FullDeck.emplace_back(CardID::FebruaryAnimal, CardSuit::February, CardType::Animal);
    m_FullDeck.emplace_back(CardID::FebruaryRibbon, CardSuit::February, CardType::Ribbon);
    m_FullDeck.emplace_back(CardID::MarchBright, CardSuit::March, CardType::Bright);
    m_FullDeck.emplace_back(CardID::MarchRibbon, CardSuit::March, CardType::Ribbon);
    m_FullDeck.emplace_back(CardID::AprilAnimal, CardSuit::April, CardType::Animal);
    m_FullDeck.emplace_back(CardID::AprilRibbon, CardSuit::April, CardType::Ribbon);
    m_FullDeck.emplace_back(CardID::MayRibbon, CardSuit::May, CardType::Ribbon);
    m_FullDeck.emplace_back(CardID::MayDoubleJunk, CardSuit::May, CardType::DoubleJunk);
    m_FullDeck.emplace_back(CardID::JuneAnimal, CardSuit::June, CardType::Animal);
    m_FullDeck.emplace_back(CardID::JuneRibbon, CardSuit::June, CardType::Ribbon);
    m_FullDeck.emplace_back(CardID::JulyAnimal, CardSuit::July, CardType::Animal);
    m_FullDeck.emplace_back(CardID::JulyRibbon, CardSuit::July, CardType::Ribbon);
    m_FullDeck.emplace_back(CardID::AugustBright, CardSuit::August, CardType::Bright);
    m_FullDeck.emplace_back(CardID::AugustAnimal, CardSuit::August, CardType::Animal);
    m_FullDeck.emplace_back(CardID::SeptemberRibbon, CardSuit::September, CardType::Ribbon);
    m_FullDeck.emplace_back(CardID::SeptemberDoubleJunk, CardSuit::September, CardType::DoubleJunk);
    m_FullDeck.emplace_back(CardID::OctoberAnimal, CardSuit::October, CardType::Animal);
    m_FullDeck.emplace_back(CardID::OctoberRibbon, CardSuit::October, CardType::Ribbon);

    reshuffle();
}

void Deck::render(SDL_Renderer* renderer) const {
    for (const auto& card : m_CurrentDeck) {
        card.render(renderer);
    }
}

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(m_CurrentDeck.begin(), m_CurrentDeck.end(), g);
}

Card& Deck::deal() {
    if (m_CurrentDeck.empty()) {
        std::cerr << "[ERROR] No more cards in the deck\n";
    }

    // Deal the top card (remove from the deck)
    Card& dealtCard = m_CurrentDeck.back();
    // std::unique_ptr<Card> dealtCard = std::move(m_CurrentDeck.back());
    m_CurrentDeck.pop_back();
    return dealtCard;
}

void Deck::reshuffle() {
    m_CurrentDeck.clear();
    for (const auto& card : m_FullDeck) {
        m_CurrentDeck.emplace_back(Card(card.getCardID(), card.getSuit(), card.getType()));
        // m_CurrentDeck.emplace_back(std::make_unique<Card>(card->getCardID(), card->getSuit(), card->getType()));
    }
    shuffle();
    for (size_t i = 0; i < m_CurrentDeck.size(); ++i) {
        m_CurrentDeck[i].setPosition(Config::SCREEN_WIDTH / 2 - Config::CARD_WIDTH / 2, Config::SCREEN_HEIGHT / 2 - Config::CARD_HEIGHT / 2 - i);
    }
}

bool Deck::isEmpty() const {
    return m_CurrentDeck.empty();
}

void Deck::printDeck() const {
    for (const auto& card : m_CurrentDeck) {
        card.printCard();
    }
}

std::vector<Card>& Deck::getCurrentDeck() {
    return m_CurrentDeck;
}
const std::vector<Card>& Deck::getCurrentDeck() const {
    return m_CurrentDeck;
}

