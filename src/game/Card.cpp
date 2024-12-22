#include <iostream>
#include <SDL_image.h>

#include "game/Card.h"

Card::Card(CardSuit s, CardType t, SDL_Renderer* renderer) : suit(s), type(t), renderer(renderer)
{
    if (!loadTexture())
        std::cerr << "Failed to load image: " << SDL_GetError() << std::endl;

    rect.x = 50;
    rect.y = 50;
    rect.w = 46;
    rect.h = 72;
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

void Card::render(SDL_Renderer* renderer)
{
    if (texture != nullptr) {
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
    }
}

void Card::handleEvent(const SDL_Event& event)
{

}

bool Card::loadTexture()
{
    std::string imagePath = getCardImage();
    SDL_Surface* surface = IMG_Load(imagePath.c_str());

    if (surface == nullptr)
    {
        return false;
    }
    
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    return true;
}

std::string Card::getCardImage() const
{
    std::string imageName;

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

    return imageName;
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