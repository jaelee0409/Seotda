#include <iostream>
#include <SDL_image.h>

#include "Config.h"
#include "Card.h"
#include "Game.h"

SDL_Texture* Card::s_FaceDownTexture = nullptr;

Card::Card()
    : m_Id(CardID::JanuaryBright), m_Suit(CardSuit::January), m_Type(CardType::Bright), m_Renderer(nullptr), m_FaceUpTexture(nullptr), m_IsFaceUp(false) {

}

Card::Card(CardID id, CardSuit s, CardType t, SDL_Renderer* _renderer)
    : m_Id(id), m_Suit(s), m_Type(t), m_Renderer(_renderer), m_FaceUpTexture(nullptr), m_IsFaceUp(false) {

    if (!loadTexture()) {
        std::cerr << "Failed to load image: " << SDL_GetError() << std::endl;
        return;
    }

    setRect(Config::SCREEN_WIDTH / 2 - Config::CARD_WIDTH / 2, Config::SCREEN_HEIGHT / 2 - Config::CARD_HEIGHT / 2, Config::CARD_WIDTH, Config::CARD_HEIGHT);
}

Card::~Card() {
    if (m_FaceUpTexture == nullptr)
        return;

    SDL_DestroyTexture(m_FaceUpTexture);
    m_FaceUpTexture = nullptr;
}

bool Card::loadFaceDownTexture(SDL_Renderer* renderer) {
    if (s_FaceDownTexture == nullptr) {
        s_FaceDownTexture = IMG_LoadTexture(renderer, "assets/images/cards/face_down.png");
        if (s_FaceDownTexture == nullptr) {
            std::cerr << "Failed to load face down card texture: " << IMG_GetError() << std::endl;
            return false;
        }
    }
    return true;
}

SDL_Texture* Card::getFaceDownTexture() {
    return s_FaceDownTexture;
}

void Card::setFaceDownTexture(SDL_Texture* texture) {
    s_FaceDownTexture = texture;
}

void Card::destroyFaceDownTexture() {
    if (s_FaceDownTexture == nullptr)
        return;

    SDL_DestroyTexture(s_FaceDownTexture);
    s_FaceDownTexture = nullptr;
}

void Card::update() {

}

void Card::render() const {
    // if (getCurrentGameState() != GameStateEnum::Gameplay) // TODO: If you are not in the gameplay state
    //     return;

    if (m_IsFaceUp) {
        if (SDL_RenderCopy(m_Renderer, m_FaceUpTexture, nullptr, &m_Rect) != 0) {
            std::cerr << "Error rendering card face up: " << SDL_GetError() << std::endl;
        }
    }
    else {
        if (SDL_RenderCopy(m_Renderer, s_FaceDownTexture, nullptr, &m_Rect) != 0) {
            std::cerr << "Error rendering card face down: " << SDL_GetError() << std::endl;
        }
    }
}

void Card::handleEvent(const SDL_Event& event) {

}

bool Card::loadTexture() {
    std::string imagePath = getCardImagePath();
    SDL_Surface* surface = IMG_Load(imagePath.c_str());
    if (surface == nullptr) {
        std::cerr << "IMG_Load error: " << IMG_GetError() << std::endl;
        return false;
    }
    
    m_FaceUpTexture = SDL_CreateTextureFromSurface(m_Renderer, surface);
    if (m_FaceUpTexture == nullptr) {
        std::cerr << "Failed to create face up texture from surface: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_FreeSurface(surface);

    return true;
}

std::string Card::getCardImagePath() const {
    std::string basePath = "assets/images/cards/";
    std::string imageName = "";

    switch (m_Suit) {
        case CardSuit::January:
            imageName += "january";
            break;

        case CardSuit::February:
            imageName += "february";
            break;

        case CardSuit::March:
            imageName += "march";
            break;

        case CardSuit::April:
            imageName += "april";
            break;

        case CardSuit::May:
            imageName += "may";
            break;

        case CardSuit::June:
            imageName += "june";
            break;

        case CardSuit::July:
            imageName += "july";
            break;

        case CardSuit::August:
            imageName += "august";
            break;

        case CardSuit::September:
            imageName += "september";
            break;

        case CardSuit::October:
            imageName += "october";
            break;

        case CardSuit::November:
            imageName += "november";
            break;

        case CardSuit::December:
            imageName += "december";
            break;

        default:
            imageName += "unknown";
            break;
    }

    switch (m_Type) {
        case CardType::Bright:
            imageName += "_bright";
            break;

        case CardType::Animal:
            imageName += "_animal";
            break;

        case CardType::Ribbon:
            imageName += "_ribbon";
            break;

        case CardType::Junk_1:
            imageName += "_junk_1";
            break;

        case CardType::Junk_2:
            imageName += "_junk_2";
            break;

        case CardType::DoubleJunk:
            imageName += "_double_junk";
            break;

        default:
            imageName += "_unknown";
            break;
    }

    imageName += ".png";

    return basePath + imageName;
}

void Card::printCard() const {
    std::cout << "Card: " << getCardTypeName(m_Type) << " of " << getCardSuitName(m_Suit) << std::endl;
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

int Card::getPositionX() const {
    return m_Rect.x;
}

int Card::getPositionY() const {
    return m_Rect.y;
}

void Card::setPositionX(int x) {
    m_Rect.x = x;
}

void Card::setPositionY(int y) {
    m_Rect.y = y;
}

void Card::setPosition(int x, int y) {
    m_Rect.x = x;
    m_Rect.y = y;
}

const SDL_Rect& Card::getRect() const {
    return m_Rect;
}

void Card::setRect(int x, int y, int w, int h) {
    m_Rect.x = x;
    m_Rect.y = y;
    m_Rect.w = w;
    m_Rect.h = h;
}

CardID Card::getCardID() const {
    return m_Id;
}
