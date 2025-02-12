#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <map>

class Chip {
    public:
        Chip(int x, int y, int value, SDL_Renderer* renderer);
        ~Chip();

        void render() const;
        int getValue() const { return m_Value; }
        void setPosition(int x, int y);
    
        static bool loadChipTextures(SDL_Renderer* renderer);
        static void destroyChipTextures();
        static SDL_Texture* getTextureForValue(int value);
    private:
        static std::map<int, SDL_Texture*> s_ChipTextures;
        SDL_Rect m_Rect;
        SDL_Renderer* m_Renderer;
        int m_Value;
};