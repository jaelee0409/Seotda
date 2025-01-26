#pragma once

#include <SDL.h>
#include <string>

#include "GameObject.h"

enum class CardSuit : uint8_t {
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

enum class CardType : uint8_t {
    Bright = 0,
    Animal,
    Ribbon,
    Junk_1,
    Junk_2,
    DoubleJunk
};

enum class CardID : uint8_t {
    JanuaryBright = 10,
    JanuaryRibbon = 12,
    FebruaryAnimal = 21,
    FebruaryRibbon = 22,
    MarchBright = 30,
    MarchRibbon = 32,
    AprilAnimal = 41,
    AprilRibbon = 42,
    MayRibbon = 52,
    MayDoubleJunk = 55,
    JuneAnimal = 61,
    JuneRibbon = 62,
    JulyAnimal = 71,
    JulyRibbon = 72,
    AugustBright = 80,
    AugustAnimal = 81,
    SeptemberRibbon = 92,
    SeptemberDoubleJunk = 95,
    OctoberAnimal = 101,
    OctoberRibbon = 102
};

class Card : public GameObject {
    public:
        Card(CardID id, CardSuit s, CardType t, SDL_Renderer* renderer);
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
        CardID getCardID() const;

    private:
        static std::string getCardSuitName(CardSuit s);
        static std::string getCardTypeName(CardType t);

        bool loadTexture();

        static SDL_Texture* s_FaceDownTexture;

        SDL_Rect m_Rect;
        SDL_Renderer* m_Renderer;
        SDL_Texture* m_FaceUpTexture;
        CardID m_Id;
        CardSuit m_Suit;
        CardType m_Type;
        bool m_IsFaceUp;
};
