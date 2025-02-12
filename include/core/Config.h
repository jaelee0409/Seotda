#pragma once

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

    inline std::string getAssetPath(const std::string& relativePath) {
        std::string buildPath = std::filesystem::current_path().string() + "/assets/" + relativePath;
        std::string rootPath = std::filesystem::current_path().string() + "/../assets/" + relativePath;

        // Check if file exists in `build/assets/`
        if (std::filesystem::exists(buildPath)) {
            return buildPath;
        }

        // Otherwise, use `../assets/`
        if (std::filesystem::exists(rootPath)) {
            return rootPath;
        }

        // If file doesn't exist, print warning and return default path
        std::cerr << "[Error] Asset not found! Returning default path: assets/" << relativePath << std::endl;
        return "assets/" + relativePath;
    }
}
