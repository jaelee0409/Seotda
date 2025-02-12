#pragma once

#include "Screen.h"

class OptionsScreen : public Screen {
    public:
        OptionsScreen(SDL_Renderer* renderer);
        
        void handleEvent(SDL_Event& event) override;
        void update() override;
        void render() override;
};