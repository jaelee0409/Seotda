#pragma once

#include "Screen.h"

class RulesScreen : public Screen {
    public:
        RulesScreen(SDL_Renderer* renderer);
        
        void handleEvent(SDL_Event& event) override;
        void update() override;
        void render() override;
};