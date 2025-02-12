#pragma once

#include <SDL.h>
#include <string>
#include <filesystem>
#include <iostream>

namespace Config {
    constexpr int SCREEN_WIDTH = 1280;
    constexpr int SCREEN_HEIGHT = 720;
    
    constexpr int CARD_WIDTH = 46;
    constexpr int CARD_HEIGHT = 72;

    constexpr int MAIN_MENU_BUTTON_WIDTH = 200;
    constexpr int MAIN_MENU_BUTTON_HEIGHT = 50;

    constexpr int PLAYER_ACTION_BUTTON_WIDTH = 100;
    constexpr int PLAYER_ACTION_BUTTON_HEIGHT = 50;

    constexpr int CHIP_WIDTH = 48;
    constexpr int CHIP_HEIGHT = 48;

    constexpr int PLAYER_COUNT = 5;
    constexpr int STARTING_MONEY = 10'000'000;

    

    static std::string detectBasePath() {
        char* base = SDL_GetBasePath();
        if (!base) {
            // fallback if SDL_GetBasePath() fails
            return "./";
        }

        std::string s(base);
        SDL_free(base);

        std::filesystem::path exePath(s);

        // 1) If path ends in a slash, `exePath.filename()` is empty
        //    so let’s remove the trailing slash by going to parent_path().
        if (exePath.filename().string().empty()) {
            exePath = exePath.parent_path(); 
            // e.g. "C:\msys64\home\jaele\projects\Seotda\build"
        }

        // 2) Now if the last folder is "build", move up one level
        if (exePath.filename().string() == "build") {
            exePath = exePath.parent_path();
            // e.g. "C:\msys64\home\jaele\projects\Seotda"
        }

        // 3) Return with trailing slash
        //    This ensures final string ends with "/"
        return exePath.string() + "/";
    }

    static std::string getBasePath() {
        static std::string basePath = detectBasePath();
        return basePath;
    }

    static std::string getAssetPath(const std::string& relativePath) {
        return getBasePath() + "assets/" + relativePath;
    }
}
