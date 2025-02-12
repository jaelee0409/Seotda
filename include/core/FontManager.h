#pragma once

#include <SDL_ttf.h>
#include <map>
#include <string>

/**
 * A simple pointer-based singleton for managing TTF fonts.
 */
class FontManager {
public:
    // Constructor sets 'this' as the singleton instance
    FontManager();
    ~FontManager();

    // Access the singleton
    static FontManager* getInstance();

    // Load a TTF font from a file path, store under a fontID string
    bool loadFont(const std::string& fontID, const std::string& filePath, int fontSize);

    // Retrieve a font by fontID
    TTF_Font* getFont(const std::string& fontID);

    // Optionally free all fonts
    void cleanup();

private:
    static FontManager* s_Instance;
    std::map<std::string, TTF_Font*> m_FontMap;
};
