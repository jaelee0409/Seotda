#include <SDL_image.h>
#include <iostream>
#include <memory>

#include "core/CardTextureManager.h"

CardTextureManager* CardTextureManager::s_Instance = nullptr;

CardTextureManager::CardTextureManager(SDL_Renderer* renderer) : m_Renderer(renderer) {
    s_Instance = this;
}

CardTextureManager* CardTextureManager::getInstance() {
    return s_Instance;
}

bool CardTextureManager::loadFaceDownTexture(const std::string& filePath) {
    if (m_FaceDownTexture) {
        // Already loaded
        return true;
    }
    m_FaceDownTexture = loadTexture(filePath);

    return true;
}

bool CardTextureManager::loadFaceUpTexture(CardID id, const std::string& filePath) {
    if (m_FaceUpMap.find(id) != m_FaceUpMap.end()) {
        // Already loaded
        return true;
    }
    SDL_Texture* texture = loadTexture(filePath);

    m_FaceUpMap[id] = texture;
    return true;
}

SDL_Texture* CardTextureManager::getFaceDownTexture() const {
    return m_FaceDownTexture;
}

SDL_Texture* CardTextureManager::getFaceUpTexture(CardID id) const {
    auto it = m_FaceUpMap.find(id);
    if (it != m_FaceUpMap.end()) {
        return it->second;
    }

    std::cerr << "[ERROR] Failed to get face up texture\n";
    return nullptr;
}

bool CardTextureManager::loadAllTextures() {
    if (!loadFaceDownTexture("assets/images/cards/face_down.png"))
        return false;

    if (!loadFaceUpTexture(CardID::JanuaryBright, getCardImagePathById(CardID::JanuaryBright)))
        return false;
    if (!loadFaceUpTexture(CardID::JanuaryRibbon, getCardImagePathById(CardID::JanuaryRibbon)))
        return false;
    if (!loadFaceUpTexture(CardID::FebruaryAnimal, getCardImagePathById(CardID::FebruaryAnimal)))
        return false;
    if (!loadFaceUpTexture(CardID::FebruaryRibbon, getCardImagePathById(CardID::FebruaryRibbon)))
        return false;
    if (!loadFaceUpTexture(CardID::MarchBright, getCardImagePathById(CardID::MarchBright)))
        return false;
    if (!loadFaceUpTexture(CardID::MarchRibbon, getCardImagePathById(CardID::MarchRibbon)))
        return false;
    if (!loadFaceUpTexture(CardID::AprilAnimal, getCardImagePathById(CardID::AprilAnimal)))
        return false;
    if (!loadFaceUpTexture(CardID::AprilRibbon, getCardImagePathById(CardID::AprilRibbon)))
        return false;
    if (!loadFaceUpTexture(CardID::MayRibbon, getCardImagePathById(CardID::MayRibbon)))
        return false;
    if (!loadFaceUpTexture(CardID::MayDoubleJunk, getCardImagePathById(CardID::MayDoubleJunk)))
        return false;
    if (!loadFaceUpTexture(CardID::JuneAnimal, getCardImagePathById(CardID::JuneAnimal)))
        return false;
    if (!loadFaceUpTexture(CardID::JuneRibbon, getCardImagePathById(CardID::JuneRibbon)))
        return false;
    if (!loadFaceUpTexture(CardID::JulyAnimal, getCardImagePathById(CardID::JulyAnimal)))
        return false;
    if (!loadFaceUpTexture(CardID::JulyRibbon, getCardImagePathById(CardID::JulyRibbon)))
        return false;
    if (!loadFaceUpTexture(CardID::AugustBright, getCardImagePathById(CardID::AugustBright)))
        return false;
    if (!loadFaceUpTexture(CardID::AugustAnimal, getCardImagePathById(CardID::AugustAnimal)))
        return false;
    if (!loadFaceUpTexture(CardID::SeptemberRibbon, getCardImagePathById(CardID::SeptemberRibbon)))
        return false;
    if (!loadFaceUpTexture(CardID::SeptemberDoubleJunk, getCardImagePathById(CardID::SeptemberDoubleJunk)))
        return false;
    if (!loadFaceUpTexture(CardID::OctoberAnimal, getCardImagePathById(CardID::OctoberAnimal)))
        return false;
    if (!loadFaceUpTexture(CardID::OctoberRibbon, getCardImagePathById(CardID::OctoberRibbon)))
        return false;
    
        

    return true;
}

void CardTextureManager::destroyAllTextures() {
    // Destroy face-down
    if (m_FaceDownTexture) {
        SDL_DestroyTexture(m_FaceDownTexture);
        m_FaceDownTexture = nullptr;
    }
    // Destroy face-up
    for (auto& kv : m_FaceUpMap) {
        if (kv.second) {
            SDL_DestroyTexture(kv.second);
            kv.second = nullptr;
        }
    }
    m_FaceUpMap.clear();
}

SDL_Texture* CardTextureManager::loadTexture(const std::string& filePath) {
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface) {
        std::cerr << "[CardTextureManager] IMG_Load failed for " 
                  << filePath << ": " << IMG_GetError() << "\n";
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_Renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        std::cerr << "[CardTextureManager] SDL_CreateTextureFromSurface failed for "
                  << filePath << ": " << SDL_GetError() << "\n";
    }
    return texture;
}

std::string CardTextureManager::getCardImagePathById(CardID id) const {
    std::string basePath = "assets/images/cards/";
    std::string imageName;

    switch (id) {
        case CardID::JanuaryBright:
            imageName = "january_bright";
            break;
        case CardID::JanuaryRibbon:
            imageName = "january_ribbon";
            break;
        case CardID::FebruaryAnimal:
            imageName = "february_animal";
            break;
        case CardID::FebruaryRibbon:
            imageName = "february_ribbon";
            break;
        case CardID::MarchBright:
            imageName = "march_bright";
            break;
        case CardID::MarchRibbon:
            imageName = "march_ribbon";
            break;
        case CardID::AprilAnimal:
            imageName = "april_animal";
            break;
        case CardID::AprilRibbon:
            imageName = "april_ribbon";
            break;
        case CardID::MayRibbon:
            imageName = "may_ribbon";
            break;
        case CardID::MayDoubleJunk:
            imageName = "may_double_junk";
            break;
        case CardID::JuneAnimal:
            imageName = "june_animal";
            break;
        case CardID::JuneRibbon:
            imageName = "june_ribbon";
            break;
        case CardID::JulyAnimal:
            imageName = "july_animal";
            break;
        case CardID::JulyRibbon:
            imageName = "july_ribbon";
            break;
        case CardID::AugustBright:
            imageName = "august_bright";
            break;
        case CardID::AugustAnimal:
            imageName = "august_animal";
            break;
        case CardID::SeptemberRibbon:
            imageName = "september_ribbon";
            break;
        case CardID::SeptemberDoubleJunk:
            imageName = "september_double_junk";
            break;
        case CardID::OctoberAnimal:
            imageName = "october_animal";
            break;
        case CardID::OctoberRibbon:
            imageName = "october_ribbon";
            break;
        default:
            imageName = "unknown";
            break;
    }

    return basePath + imageName + ".png";
}
