#pragma once

#include <SDL.h>

#include "GameObject.h"

class Card : public GameObject
{
    public:
        enum class CardName {
            JanuaryBright = 0,
            JanuaryRibbon,
            JanuaryJunk1,
            JanuaryJunk2,
            FebruaryAnimal,
            FebruaryRibbon,
            FebruaryJunk1,
            FebruaryJunk2,
            
        };

        Card(CardName name);
        ~Card();

        void update() override;
        void render(SDL_Renderer* renderer) override;
        void handleEvent(const SDL_Event& event) override;

    private:
        SDL_Rect rect;
        CardName name;
};
