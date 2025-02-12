#include <iostream>
#include <SDL_image.h>

#include "core/Config.h"
#include "core/Game.h"
#include "game/Card.h"

Card::Card(CardID id, CardSuit s, CardType t) : m_Id(id), m_Suit(s), m_Type(t) {

}

Card::~Card() {

}

void Card::update() {
    if (m_IsMoving) {
        Uint32 elapsed = SDL_GetTicks() - m_MoveStartTime;
        if (elapsed >= m_MoveDuration) {
            // Animation is over
            m_IsMoving = false;
            m_Position = m_TargetPos;
        } else {
            // Smooth movement using interpolation
            float t = (float)elapsed / (float)m_MoveDuration;
            int newX = (int)(m_StartPos.x + t * (m_TargetPos.x - m_StartPos.x));
            int newY = (int)(m_StartPos.y + t * (m_TargetPos.y - m_StartPos.y));
            m_Position = { newX, newY };
        }
    }
}

void Card::render(SDL_Renderer* renderer) const {
    if (!renderer) {
        std::cerr << "[ERROR] Card : Renderer is null\n";
        return;
    }

    SDL_Texture* texture = m_IsFaceUp ? CardTextureManager::getInstance()->getFaceUpTexture(m_Id) : CardTextureManager::getInstance()->getFaceDownTexture();

    SDL_Rect destRect{ m_Position.x, m_Position.y, Config::CARD_WIDTH, Config::CARD_HEIGHT };
    if (SDL_RenderCopy(renderer, texture, nullptr, &destRect) != 0) {
        std::cerr << "[ERROR] Card : Rendering card: " << SDL_GetError() << std::endl;
    }
}

void Card::startMoving(int targetX, int targetY, Uint32 duration) {
    m_IsMoving = true;
    m_StartPos = m_Position;
    m_TargetPos = { targetX, targetY };
    m_MoveStartTime = SDL_GetTicks();
    m_MoveDuration  = duration;
}

void Card::printCard() const {
    std::cout << "Card: " << getCardTypeName(m_Type) << " of " << getCardSuitName(m_Suit) << std::endl;
}

bool Card::isFaceUp() const {
    return m_IsFaceUp;
}

std::string Card::getCardTypeName(CardType t) {
    switch(t) {
        case CardType::Bright:
            return "Bright";

        case CardType::Animal:
            return "Animal";

        case CardType::Ribbon:
            return "Ribbon";

        case CardType::Junk_1:
            return "Junk 1";

        case CardType::Junk_2:
            return "Junk 2";

        case CardType::DoubleJunk:
            return "Double Junk";

        default:
            return "Unknown";
    }
}

std::string Card::getCardSuitName(CardSuit s) {
    switch(s) {
        case CardSuit::January:
            return "January";

        case CardSuit::February:
            return "February";

        case CardSuit::March:
            return "March";

        case CardSuit::April:
            return "April";

        case CardSuit::May:
            return "May";

        case CardSuit::June:
            return "June";

        case CardSuit::July:
            return "July";

        case CardSuit::August:
            return "August";

        case CardSuit::September:
            return "September";

        case CardSuit::October:
            return "October";

        case CardSuit::November:
            return "November";

        case CardSuit::December:
            return "December";

        default:
            return "Unknown";
    }
}

void Card::flip() {
    m_IsFaceUp = !m_IsFaceUp;
}

void Card::setPosition(int x, int y) {
    m_Position.x = x;
    m_Position.y = y;
    m_IsMoving = false;
}

SDL_Point Card::getPosition() const {
    return m_Position;
}


CardID Card::getCardID() const {
    return m_Id;
}
