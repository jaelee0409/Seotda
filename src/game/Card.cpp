#include <iostream>
#include <SDL_image.h>

#include "Config.h"
#include "game/Card.h"

Card::Card(CardSuit s, CardType t, SDL_Renderer* _renderer) : suit(s), type(t), renderer(_renderer)
{
    if (!loadTexture()) {
        std::cerr << "Failed to load image: " << SDL_GetError() << std::endl;
        return;
    }
        
    rect.x = Config::SCREEN_WIDTH / 2 - Config::CARD_WIDTH / 2;
    rect.y = Config::SCREEN_HEIGHT / 2 - Config::CARD_HEIGHT / 2;
    rect.w = Config::CARD_WIDTH;
    rect.h = Config::CARD_HEIGHT;
}

Card::~Card()
{
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Card::update()
{

}

void Card::render() const
{
    if (texture != nullptr) {
        if (SDL_RenderCopy(renderer, texture, nullptr, &rect) != 0) {
            std::cerr << "Error rendering card: " << SDL_GetError() << std::endl;
        }
    } else {
        std::cerr << "Texture is nullptr for card: " << getCardSuitName(suit) << " " << getCardTypeName(type) << std::endl;
    }
}

void Card::handleEvent(const SDL_Event& event)
{

}

bool Card::loadTexture()
{
    std::string imagePath = getCardImagePath();
    SDL_Surface* surface = IMG_Load(imagePath.c_str());
    if (surface == nullptr)
    {
        std::cerr << "IMG_Load error: " << IMG_GetError() << std::endl;
        return false;
    }
    
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr) {
        std::cerr << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_FreeSurface(surface);

    return true;
}

std::string Card::getCardImagePath() const
{
    std::string basePath = "assets/images/cards/";
    std::string imageName = "";

    switch (suit)
    {
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

    switch (type)
    {
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

SDL_Texture* Card::getCardTexture() const
{
    return texture;
}

void Card::printCard() const
{
    std::cout << "Card: " << getCardTypeName(type) << " of " << getCardSuitName(suit) << std::endl;
}

std::string Card::getCardTypeName(CardType t)
{
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

std::string Card::getCardSuitName(CardSuit s)
{
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

int Card::getPositionX() const
{
    return rect.x;
}

int Card::getPositionY() const
{
    return rect.y;
}

void Card::setPosition(int x, int y)
{
    rect.x = x;
    rect.y = y;
}
