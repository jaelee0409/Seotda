#pragma once

#include <SDL.h>
#include <SDL_image.h>

class Chip {
    public:
        Chip();
        ~Chip()

    private:
        static SDL_Texture* s_ChipTexture;
        SDL_Rect m_Rect;
        SDL_Renderer* m_Renderer;
        int m_Value;
};