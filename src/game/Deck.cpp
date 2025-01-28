#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <memory>
#include <SDL_image.h>

#include "Deck.h"
#include "Card.h"

SDL_Texture* Deck::s_FaceDownTexture = nullptr;

Deck::Deck(SDL_Renderer* renderer) {
}

Deck::~Deck() {
    m_Renderer = nullptr;
}

bool Deck::loadFaceDownTexture(SDL_Renderer* renderer) {
    if (s_FaceDownTexture == nullptr) {
        s_FaceDownTexture = IMG_LoadTexture(renderer, "assets/images/cards/face_down.png");
        if (s_FaceDownTexture == nullptr) {
            std::cerr << "Failed to load face down card texture: " << IMG_GetError() << std::endl;
            return false;
        }
    }
    return true;
}

SDL_Texture* Deck::getFaceDownTexture() {
    return s_FaceDownTexture;
}

void Deck::setFaceDownTexture(SDL_Texture* texture) {
    s_FaceDownTexture = texture;
}

void Deck::destroyFaceDownTexture() {
    if (s_FaceDownTexture == nullptr)
        return;

    SDL_DestroyTexture(s_FaceDownTexture);
    s_FaceDownTexture = nullptr;
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
}

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(m_CurrentDeck.begin(), m_CurrentDeck.end(), g);
}

Card Deck::deal() {
    if (m_CurrentDeck.empty()) {
        std::cerr << "No more cards in the deck!" << std::endl;
        return Card();
    }

    // Deal the top card (remove from the deck)
    Card dealtCard = m_CurrentDeck.back();
    m_CurrentDeck.pop_back();
    return dealtCard;
}

void Deck::reset() {
    m_CurrentDeck.clear();
    for (auto& card : m_FullDeck) {
        m_CurrentDeck.push_back(card);
    }
    shuffle();

    for (size_t i = 0; i < m_CurrentDeck.size(); ++i) {
        m_CurrentDeck[i].setPosition(m_CurrentDeck[i].getPositionX() + i, m_CurrentDeck[i].getPositionY() - i);
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

const std::vector<Card>& Deck::getDeck() const {
    return m_CurrentDeck;
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