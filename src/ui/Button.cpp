#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "ui/Button.h"

Button::Button(int x, int y, int width, int height, const std::string& text, std::function<void()> onClick, TTF_Font* font)
: m_Rect{x, y, width, height}, m_Text(text), m_OnClick(onClick), m_IsHovered(false), m_Font(font), m_TextTexture(nullptr), m_TextColor{255, 255, 255, 255} {

}

Button::~Button() {
    if (m_TextTexture) {
        SDL_DestroyTexture(m_TextTexture);
        m_TextTexture = nullptr;
    }
}

void Button::handleEvent(SDL_Event& event) {
    if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        bool inside = (mouseX >= m_Rect.x && mouseX <= (m_Rect.x + m_Rect.w) &&
                       mouseY >= m_Rect.y && mouseY <= (m_Rect.y + m_Rect.h));

        m_IsHovered = inside;

        if (inside && event.type == SDL_MOUSEBUTTONDOWN) {
            if (m_OnClick) {
                m_OnClick();
            }
        }
    }
}

void Button::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, m_IsHovered ? 150 : 200, m_IsHovered ? 150 : 200, m_IsHovered ? 150 : 200, 255);
    SDL_RenderFillRect(renderer, &m_Rect);
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &m_Rect);

    if (!m_Font) {
        std::cerr << "[ERROR] Button tried to render with nullptr font\n";
        return;
    }

    // Render text
    if (!m_TextTexture) {
        createTextTexture(renderer);
    }

    if (m_TextTexture) {
        int textWidth, textHeight;
        SDL_QueryTexture(m_TextTexture, nullptr, nullptr, &textWidth, &textHeight);
        SDL_Rect textRect = { m_Rect.x + (m_Rect.w - textWidth) / 2, m_Rect.y + (m_Rect.h - textHeight) / 2, textWidth, textHeight };
        SDL_RenderCopy(renderer, m_TextTexture, nullptr, &textRect);
    }
}

void Button::createTextTexture(SDL_Renderer* renderer) {
    if (!m_Font) {
        std::cerr << "[ERROR] Button font is nullptr\n";
        return;
    }

    SDL_Surface* textSurface = TTF_RenderText_Solid(m_Font, m_Text.c_str(), m_TextColor);
    if (!textSurface) {
        std::cerr << "[ERROR] Button text surface creation failed: " << TTF_GetError() << std::endl;
        return;
    }

    m_TextTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
}