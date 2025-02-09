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
        Card();
        Card(CardID id, CardSuit s, CardType t, SDL_Renderer* renderer);
        ~Card();

        // Prevent accidental copies
        Card(const Card&) = delete;
        Card& operator=(const Card&) = delete;

        // Allow moves to safely transfer ownership
        Card(Card&& other) noexcept;
        Card& operator=(Card&& other) noexcept;

        void update() override;
        void render() const override;
        void handleEvent(const SDL_Event& event) override;
        
        void startMoving(const SDL_Rect& targetPos, Uint32 duration);
        std::string getCardImagePath() const;
        void printCard() const;
        bool isFaceUp() const;
        void flip();
        int getPositionX() const;
        int getPositionY() const;
        void setPositionX(int x);
        void setPositionY(int y);
        void setPosition(int x, int y);
        const SDL_Rect& getRect() const;
        CardSuit getSuit() const { return m_Suit; }
        CardType getType() const { return m_Type; }
        void setRect(int x, int y, int w, int h);
        CardID getCardID() const;

        static std::string getCardSuitName(CardSuit s);
        static std::string getCardTypeName(CardType t);      

        static bool loadFaceDownTexture(SDL_Renderer* renderer);
        static void destroyFaceDownTexture();
        static SDL_Texture* getFaceDownTexture();
    private:
        bool loadTexture();

        SDL_Rect m_Rect, m_TargetPos;
        Uint32 m_MoveStartTime = 0, m_MoveDuration = 0;
        SDL_Renderer* m_Renderer;
        SDL_Texture* m_FaceUpTexture;
        static SDL_Texture* s_FaceDownTexture;
        CardID m_Id;
        CardSuit m_Suit;
        CardType m_Type;
        bool m_IsFaceUp;
        bool m_IsMoving;
};
