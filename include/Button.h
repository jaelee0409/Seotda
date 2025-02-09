#pragma once

#include <SDL.h>
#include <string>

class Button {
    public:
        Button(int x, int y, int w, int h, SDL_Renderer* renderer, const std::string& texturePath);
        
        ~Button();
        
        void render() const;
        bool isClicked(int mouseX, int mouseY) const;
        
    private:
        int m_X, m_Y, m_Width, m_Height;
        SDL_Renderer* m_Renderer;
        SDL_Texture* m_Texture;
};
