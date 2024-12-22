#pragma once

#include <SDL.h>

class GameObject {
    public:
        virtual ~GameObject() = default;
    
        virtual void update() = 0;
        virtual void render(SDL_Renderer* renderer) = 0;
        virtual void handleEvent(const SDL_Event& event) = 0;
};
