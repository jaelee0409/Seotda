#include <iostream>

#include "core/FontManager.h"

// Define the static pointer
FontManager* FontManager::s_Instance = nullptr;

FontManager::FontManager() {
    // If you want to ensure a single instance, you could do an assertion here
    // if (s_Instance) { std::cerr << "[FontManager] Warning: multiple FontManagers!\n"; }
    s_Instance = this;
}

FontManager::~FontManager() {
    // If this is the current instance, set to null
    if (s_Instance == this) {
        s_Instance = nullptr;
    }
    // Optionally call cleanup() if you prefer automatic freeing
    cleanup();
}

FontManager* FontManager::getInstance() {
    return s_Instance;
}

bool FontManager::loadFont(const std::string& fontID, const std::string& filePath, int fontSize) {
    TTF_Font* font = TTF_OpenFont(filePath.c_str(), fontSize);
    if (!font) {
        std::cerr << "[ERROR] Failed to load font '" << fontID
                  << "' from " << filePath << ": " << TTF_GetError() << std::endl;
        return false;
    }
    m_FontMap[fontID] = font;
    std::cout << "[DEBUG] Loaded font '" << fontID << "' from " << filePath << std::endl;
    return true;
}

TTF_Font* FontManager::getFont(const std::string& fontID) {
    auto it = m_FontMap.find(fontID);
    if (it == m_FontMap.end()) {
        std::cerr << "[ERROR] FontID '" << fontID << "' not found!\n";
        return nullptr;
    }
    return it->second;
}

void FontManager::cleanup() {
    for (auto& kv : m_FontMap) {
        if (kv.second) {
            TTF_CloseFont(kv.second);
            kv.second = nullptr;
        }
    }
    m_FontMap.clear();
}
