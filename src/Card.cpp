#include <iostream>
#include <SDL_image.h>

#include "Config.h"
#include "Card.h"
#include "Game.h"

SDL_Texture* Card::s_FaceDownTexture = nullptr;

Card::Card()
    : m_Id(CardID::JanuaryBright), m_Suit(CardSuit::January), m_Type(CardType::Bright), m_Renderer(nullptr), m_FaceUpTexture(nullptr), m_IsFaceUp(false), m_IsMoving(false) {

}

Card::Card(CardID id, CardSuit s, CardType t, SDL_Renderer* _renderer)
    : m_Id(id), m_Suit(s), m_Type(t), m_Renderer(_renderer), m_FaceUpTexture(nullptr), m_IsFaceUp(false), m_IsMoving(false) {

    if (!loadTexture()) {
        std::cerr << "Failed to load image: " << SDL_GetError() << std::endl;
        return;
    }

    setRect(Config::SCREEN_WIDTH / 2 - Config::CARD_WIDTH / 2, Config::SCREEN_HEIGHT / 2 - Config::CARD_HEIGHT / 2, Config::CARD_WIDTH, Config::CARD_HEIGHT);
}

// Move constructor
Card::Card(Card&& other) noexcept
    : m_Id(other.m_Id), m_Suit(other.m_Suit), m_Type(other.m_Type),
      m_Renderer(other.m_Renderer), m_FaceUpTexture(other.m_FaceUpTexture), m_IsFaceUp(other.m_IsFaceUp) {
    
    other.m_FaceUpTexture = nullptr; // Null out the old texture to prevent double deletion
}

// Move assignment operator
Card& Card::operator=(Card&& other) noexcept {
    if (this != &other) {
        // Free existing texture
        if (m_FaceUpTexture) {
            SDL_DestroyTexture(m_FaceUpTexture);
        }

        // Move data
        m_Id = other.m_Id;
        m_Suit = other.m_Suit;
        m_Type = other.m_Type;
        m_Renderer = other.m_Renderer;
        m_FaceUpTexture = other.m_FaceUpTexture;
        m_IsFaceUp = other.m_IsFaceUp;

        other.m_FaceUpTexture = nullptr; // Prevent double free
    }
    return *this;
}

Card::~Card() {
    if (m_FaceUpTexture) {
        SDL_DestroyTexture(m_FaceUpTexture);
        m_FaceUpTexture = nullptr;
    }
}

void Card::update() {
    if (!m_IsMoving)
        return;

    Uint32 elapsed = SDL_GetTicks() - m_MoveStartTime;
    float t = (elapsed / static_cast<float>(m_MoveDuration));

    if (t >= 1.0f) {
        m_IsMoving = false;
        m_Rect = m_TargetPos;
        return;
    }

    // Smooth movement using interpolation
    m_Rect.x = m_Rect.x + static_cast<int>((m_TargetPos.x - m_Rect.x) * t);
    m_Rect.y = m_Rect.y + static_cast<int>((m_TargetPos.y - m_Rect.y) * t);
}

void Card::render() const {
    // if (getCurrentGameState() != GameStateEnum::Gameplay) // TODO: If you are not in the gameplay state
    //     return;
    SDL_Texture* texture = m_IsFaceUp ? m_FaceUpTexture : Card::getFaceDownTexture();

    if (!texture) {
        std::cerr << "[Card::render] Error: Texture is NULL. Face up? " << m_IsFaceUp << std::endl;
        return;
    }

    if (SDL_RenderCopy(m_Renderer, texture, nullptr, &m_Rect) != 0) {
        std::cerr << "[Card::render] Error rendering card: " << SDL_GetError() << std::endl;
    }

    if (!m_Renderer) {
        std::cerr << "[Card::render] Error: Renderer is NULL!" << std::endl;
        return;
    }
}

void Card::handleEvent(const SDL_Event& event) {

}

void Card::startMoving(const SDL_Rect& targetPos, Uint32 duration) {
    m_TargetPos = targetPos;
    m_MoveStartTime = SDL_GetTicks();
    m_MoveDuration = duration;
    m_IsMoving = true;
}

bool Card::loadTexture() {
    std::string imagePath = getCardImagePath();
    SDL_Surface* surface = IMG_Load(imagePath.c_str());
    if (!surface) {
        std::cerr << "[Card::loadTexture] Error loading image: " << imagePath << " - " << IMG_GetError() << std::endl;
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

bool Card::loadFaceDownTexture(SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load("assets/images/cards/face_down.png");
    if (!surface) {
        std::cerr << "[Card] Failed to load face-down texture: " << IMG_GetError() << std::endl;
        return false;
    }

    s_FaceDownTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!s_FaceDownTexture) {
        std::cerr << "[Card] Failed to create texture from surface: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void Card::destroyFaceDownTexture() {
    if (s_FaceDownTexture) {
        SDL_DestroyTexture(s_FaceDownTexture);
        s_FaceDownTexture = nullptr;
    }
}

SDL_Texture* Card::getFaceDownTexture() {
    return s_FaceDownTexture;
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
