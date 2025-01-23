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


        Card(CardSuit s, CardType t, SDL_Renderer* renderer);
        ~Card();

        static void setFaceDownTexture(SDL_Texture* texture);
        static void destroyFaceDownTexture();

        void update() override;
        void render() const override;
        void handleEvent(const SDL_Event& event) override;
        
        std::string getCardImagePath() const;
        void printCard() const;
        void flip();
        int getPositionX() const;
        int getPositionY() const;
        void setPosition(int x, int y);

    private:
        SDL_Rect rect;
        SDL_Renderer* renderer;
        SDL_Texture* faceUpTexture;
        static SDL_Texture* faceDownTexture;
        CardSuit suit;
        CardType type;
        bool isFaceUp;

        static std::string getCardSuitName(CardSuit s);
        static std::string getCardTypeName(CardType t);

        bool loadTexture();
};
