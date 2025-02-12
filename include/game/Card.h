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

class Card {
    public:
        Card(CardID id, CardSuit s, CardType t);
        ~Card();
        
        void update();
        void render(SDL_Renderer* renderer) const;
        
        void startMoving(int targetX, int targetY, Uint32 duration);
        bool isFaceUp() const;
        void flip();

        void setPosition(int x, int y);
        SDL_Point getPosition() const;

        CardSuit getSuit() const { return m_Suit; }
        CardType getType() const { return m_Type; }
        CardID getCardID() const;

        static std::string getCardSuitName(CardSuit s);
        static std::string getCardTypeName(CardType t);      

        void printCard() const;
    private:
        CardID m_Id{0};
        CardSuit m_Suit{0};
        CardType m_Type{0};
        bool m_IsFaceUp{false};
        bool m_IsMoving{false};

        SDL_Point m_Position{0, 0};
        SDL_Point m_StartPos{0, 0};
        SDL_Point m_TargetPos{0, 0};

        Uint32 m_MoveStartTime{0};
        Uint32 m_MoveDuration{0};
};
