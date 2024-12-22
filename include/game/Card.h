#pragma once

#include <SDL.h>
#include <string>

#include "GameObject.h"

enum class CardSuit : uint8_t
{
    January = 1,
    February,
    March,
    April,
    May,
    June,
    July,
    August,
    September,
    October,
    November,
    December
};

enum class CardType : uint8_t
{
    Bright = 0,
    Animal,
    Ribbon,
    Junk_1,
    Junk_2,
    DoubleJunk
};

class Card : public GameObject
{
    public:
        CardSuit suit;
        CardType type;

        Card(CardSuit s, CardType t, SDL_Renderer* renderer);
        ~Card();

        void update() override;
        void render(SDL_Renderer* renderer) override;
        void handleEvent(const SDL_Event& event) override;
        bool loadTexture();
        std::string getCardImage() const;
        SDL_Texture* getCardTexture() const;
        void printCard() const;

    private:
        SDL_Rect rect;
        SDL_Renderer* renderer;
        SDL_Texture* texture;

        static std::string getCardSuitName(CardSuit s);
        static std::string getCardTypeName(CardType t);
};
