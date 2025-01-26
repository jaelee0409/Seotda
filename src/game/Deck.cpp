#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <memory>

#include "Deck.h"
#include "Card.h"

Deck::Deck(SDL_Renderer* renderer) {
}

Deck::~Deck() {
    m_Renderer = nullptr;
}

void Deck::initializeDeck(SDL_Renderer* renderer) {
    m_Renderer = renderer;
    m_FullDeck.push_back(Card(CardID::JanuaryBright, CardSuit::January, CardType::Bright, m_Renderer));
    m_FullDeck.push_back(Card(CardID::JanuaryRibbon, CardSuit::January, CardType::Ribbon, m_Renderer));
    m_FullDeck.push_back(Card(CardID::FebruaryAnimal, CardSuit::February, CardType::Animal, m_Renderer));
    m_FullDeck.push_back(Card(CardID::FebruaryRibbon, CardSuit::February, CardType::Ribbon, m_Renderer));
    m_FullDeck.push_back(Card(CardID::MarchBright, CardSuit::March, CardType::Bright, m_Renderer));
    m_FullDeck.push_back(Card(CardID::MarchRibbon, CardSuit::March, CardType::Ribbon, m_Renderer));
    m_FullDeck.push_back(Card(CardID::AprilAnimal, CardSuit::April, CardType::Animal, m_Renderer));
    m_FullDeck.push_back(Card(CardID::AprilRibbon, CardSuit::April, CardType::Ribbon, m_Renderer));
    m_FullDeck.push_back(Card(CardID::MayRibbon, CardSuit::May, CardType::Ribbon, m_Renderer));
    m_FullDeck.push_back(Card(CardID::MayDoubleJunk, CardSuit::May, CardType::DoubleJunk, m_Renderer));
    m_FullDeck.push_back(Card(CardID::JuneAnimal, CardSuit::June, CardType::Animal, m_Renderer));
    m_FullDeck.push_back(Card(CardID::JuneRibbon, CardSuit::June, CardType::Ribbon, m_Renderer));
    m_FullDeck.push_back(Card(CardID::JulyAnimal, CardSuit::July, CardType::Animal, m_Renderer));
    m_FullDeck.push_back(Card(CardID::JulyRibbon, CardSuit::July, CardType::Ribbon, m_Renderer));
    m_FullDeck.push_back(Card(CardID::AugustBright, CardSuit::August, CardType::Bright, m_Renderer));
    m_FullDeck.push_back(Card(CardID::AugustAnimal, CardSuit::August, CardType::Animal, m_Renderer));
    m_FullDeck.push_back(Card(CardID::SeptemberRibbon, CardSuit::September, CardType::Ribbon, m_Renderer));
    m_FullDeck.push_back(Card(CardID::SeptemberDoubleJunk, CardSuit::September, CardType::DoubleJunk, m_Renderer));
    m_FullDeck.push_back(Card(CardID::OctoberAnimal, CardSuit::October, CardType::Animal, m_Renderer));
    m_FullDeck.push_back(Card(CardID::OctoberRibbon, CardSuit::October, CardType::Ribbon, m_Renderer));

    reset();

    for (size_t i = 0; i < m_Cards.size(); ++i) {
        m_Cards[i].setPosition(m_Cards[i].getPositionX() + i, m_Cards[i].getPositionY() - i);
    }
}

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(m_Cards.begin(), m_Cards.end(), g);
}

Card Deck::deal() {
    if (m_Cards.empty()) {
        std::cerr << "No more cards in the deck!" << std::endl;
        return Card();
    }

    // Deal the top card (remove from the deck)
    Card dealtCard = m_Cards.back();
    m_Cards.pop_back();
    return dealtCard;
}

void Deck::reset() {
    m_Cards.clear();
    for (auto& card : m_FullDeck) {
        m_Cards.push_back(card);
    }
    shuffle();
}

bool Deck::isEmpty() const {
    return m_Cards.empty();
}

void Deck::printDeck() const {
    for (const auto& card : m_Cards) {
        card.printCard();
    }
}

const std::vector<Card>& Deck::getDeck() const {
    return m_Cards;
}

void Deck::animateDealCard(Card& card, const SDL_Rect& dest, float speed) {
    SDL_Rect startPos = card.getRect();
    float progress = 0.0f;

    while (progress < 1.0f) {
        progress += speed;

        int x = startPos.x + (dest.x - startPos.x) * progress;
        int y = startPos.y + (dest.y - startPos.y) * progress;

        card.setPosition(x, y);
        card.render();

        SDL_Delay(16);
    }

    card.setPosition(dest.x, dest.y);
}