#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Screen {
    public:
        explicit Screen(const std::string& name, SDL_Renderer* renderer) : screenName(name), m_Renderer(renderer) {}
        virtual ~Screen() = default;
    
        virtual void handleEvent(SDL_Event& event) = 0;
        virtual void update() = 0;
        virtual void render() = 0;
    
    protected:
        std::string screenName;
        SDL_Renderer* m_Renderer;
};