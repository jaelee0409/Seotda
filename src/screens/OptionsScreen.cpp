#include <iostream>
#include <memory>

#include "core/UIManager.h"
#include "screens/MainMenuScreen.h"
#include "screens/OptionsScreen.h"

OptionsScreen::OptionsScreen(SDL_Renderer* renderer) : Screen("OptionsScreen", renderer) {
    std::cout << "[DEBUG] OptionsScreen Loaded\n";
}

void OptionsScreen::handleEvent(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
        std::cout << "[DEBUG] Returning to Main Menu\n";
        UIManager::getInstance()->setScreen(std::make_unique<MainMenuScreen>(m_Renderer));
    }
}

void OptionsScreen::update() {}

void OptionsScreen::render() {
    SDL_SetRenderDrawColor(m_Renderer, 100, 100, 100, 255);
    SDL_RenderClear(m_Renderer);
    SDL_RenderPresent(m_Renderer);
}
