#pragma once
#include <SDL.h>
#include <map>

#include "game/Card.h"

class CardTextureManager {
    public:
        CardTextureManager(SDL_Renderer* renderer);
        ~CardTextureManager() = default;
        static CardTextureManager* getInstance();

        bool loadFaceDownTexture(const std::string& filePath);
        bool loadFaceUpTexture(CardID id, const std::string& filePath);
        bool loadAllTextures();

        SDL_Texture* getFaceDownTexture() const;
        SDL_Texture* getFaceUpTexture(CardID id) const;

        std::string getCardImagePathById(CardID id) const;

        void destroyAllTextures();

    private:
        SDL_Texture* loadTexture(const std::string& filePath);

        SDL_Texture* m_FaceDownTexture{nullptr};
        std::map<CardID, SDL_Texture*> m_FaceUpMap;
        SDL_Renderer* m_Renderer{nullptr};
        static CardTextureManager* s_Instance;
};
