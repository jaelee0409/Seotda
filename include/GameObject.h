#pragma once

#include <SDL.h>

class GameObject {
    public:
        virtual ~GameObject() = default;
    
        virtual void update() = 0;
        virtual void render() const = 0;
        virtual void handleEvent(const SDL_Event& event) = 0;
};
