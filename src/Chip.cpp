#include <iostream>
#include <vector>

#include "Chip.h"
#include "Config.h"

std::map<int, SDL_Texture*> Chip::s_ChipTextures;  // Store textures by value

Chip::Chip(int x, int y, int value, SDL_Renderer* renderer)
    : m_Renderer(renderer), m_Value(value) {
    m_Rect = { x, y, Config::CHIP_WIDTH, Config::CHIP_HEIGHT };
}

Chip::~Chip() {

}

void Chip::render() const {
    SDL_Texture* texture = getTextureForValue(m_Value);
    if (!texture) {
        std::cerr << "[Chip::render] Error: No texture for chip value " << m_Value << std::endl;
        return;
    }

    if (SDL_RenderCopy(m_Renderer, texture, nullptr, &m_Rect) != 0) {
        std::cerr << "[Chip::render] SDL Error: " << SDL_GetError() << std::endl;
    }
}

void Chip::setPosition(int x, int y) {
    m_Rect.x = x;
    m_Rect.y = y;
}

// Load textures for different chip values
bool Chip::loadChipTextures(SDL_Renderer* renderer) {
    std::vector<int> chipValues = { 1000000, 500000, 100000, 50000, 10000 };

    for (int value : chipValues) {
        std::string imagePath = "assets/images/chips/" + std::to_string(value) + ".png";
        SDL_Surface* surface = IMG_Load(imagePath.c_str());
        if (!surface) {
            std::cerr << "[Chip::loadChipTextures] Error loading: " << imagePath << " - " << IMG_GetError() << std::endl;
            return false;
        }

        s_ChipTextures[value] = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        if (!s_ChipTextures[value]) {
            std::cerr << "[Chip::loadChipTextures] Failed to create texture for " << value << ": " << SDL_GetError() << std::endl;
            return false;
        }
    }

    return true;
}

// Get texture based on chip value
SDL_Texture* Chip::getTextureForValue(int value) {
    return s_ChipTextures.count(value) ? s_ChipTextures[value] : nullptr;
}

// Cleanup chip textures
void Chip::destroyChipTextures() {
    for (auto& pair : s_ChipTextures) {
        SDL_DestroyTexture(pair.second);
    }
    s_ChipTextures.clear();
}