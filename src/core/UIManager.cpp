#include <iostream>

#include "core/UIManager.h"
#include "screens/MainMenuScreen.h"

UIManager* UIManager::s_Instance = nullptr;

UIManager::UIManager(SDL_Renderer* renderer) : m_Renderer(renderer) {
    s_Instance = this;
    currentScreen = std::make_unique<MainMenuScreen>(renderer);
}

UIManager::~UIManager() {
    if (s_Instance == this) {
        s_Instance = nullptr;
    }
}

UIManager* UIManager::getInstance() {
    return s_Instance;
}

void UIManager::setScreen(std::unique_ptr<Screen> newScreen) {
    if (currentScreen) {
        std::cout << "[DEBUG] UIManager : Deleting old screen\n";
        currentScreen.reset();
    }

    currentScreen = std::move(newScreen);
    std::cout << "[DEBUG] UIManager : Switching screen\n";
}

void UIManager::handleEvent(SDL_Event& event) {
    if (currentScreen) {
        currentScreen->handleEvent(event);
    }
}

void UIManager::update() {
    if (currentScreen) {
        currentScreen->update();
    }
}

void UIManager::render() {
    if (currentScreen) {
        currentScreen->render();
    }
}
