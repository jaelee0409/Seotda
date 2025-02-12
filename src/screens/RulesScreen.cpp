#include <iostream>
#include <memory>

#include "core/UIManager.h"
#include "screens/MainMenuScreen.h"
#include "screens/RulesScreen.h"

RulesScreen::RulesScreen(SDL_Renderer* renderer) : Screen("RulesScreen", renderer) {
    std::cout << "[DEBUG] RulesScreen Loaded\n";
}

void RulesScreen::handleEvent(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
        std::cout << "[DEBUG] Returning to Main Menu\n";
        UIManager::getInstance()->setScreen(std::make_unique<MainMenuScreen>(m_Renderer));
    }
}

void RulesScreen::update() {
    
}

void RulesScreen::render() {
    SDL_SetRenderDrawColor(m_Renderer, 50, 50, 200, 255);
    SDL_RenderClear(m_Renderer);
    SDL_RenderPresent(m_Renderer);
}
