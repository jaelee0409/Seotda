#pragma once

#include <SDL2/SDL.h>
#include <functional>
#include <string>

class Button {
    public:
        Button(int x, int y, int width, int height, const std::string& text, std::function<void()> onClick, TTF_Font* font);
        ~Button();

        void handleEvent(SDL_Event& event);
        void render(SDL_Renderer* renderer);

    private:
        SDL_Rect m_Rect;
        std::string m_Text;
        std::function<void()> m_OnClick;
        bool m_IsHovered;

        TTF_Font* m_Font;
        SDL_Texture* m_TextTexture;
        SDL_Color m_TextColor;
        
        void createTextTexture(SDL_Renderer* renderer);
};
