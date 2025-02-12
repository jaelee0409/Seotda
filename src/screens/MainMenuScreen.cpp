#include <iostream>
#include <algorithm>

#include "core/Config.h"
#include "core/UIManager.h"
#include "core/FontManager.h"
#include "screens/MainMenuScreen.h"
#include "screens/GameScreen.h"
#include "screens/RulesScreen.h"
#include "screens/OptionsScreen.h"

MainMenuScreen::MainMenuScreen(SDL_Renderer* renderer) : Screen("MainMenuScreen", renderer) {
    m_Font = FontManager::getInstance()->getFont("Arial24");
    if (!m_Font) {
        std::cerr << "[ERROR] Font 'Arial24' not found in Font Manager\n";
    }

    SDL_Renderer* localRenderer = renderer;

    auto startButton = std::make_unique<Button>(Config::SCREEN_WIDTH / 2 - Config::MAIN_MENU_BUTTON_WIDTH / 2, 200, Config::MAIN_MENU_BUTTON_WIDTH, Config::MAIN_MENU_BUTTON_HEIGHT,
                                                "Start",
                                                [localRenderer]() {
                                                    std::cout << "[DEBUG] Switching to Game Screen\n";
                                                    if (UIManager::getInstance()) {
                                                        UIManager::getInstance()->setScreen(std::make_unique<GameScreen>(localRenderer));
                                                    }
                                                },
                                                m_Font);
    auto rulesButton = std::make_unique<Button>(Config::SCREEN_WIDTH / 2 - Config::MAIN_MENU_BUTTON_WIDTH / 2, 300, Config::MAIN_MENU_BUTTON_WIDTH, Config::MAIN_MENU_BUTTON_HEIGHT,
                                                "Rules",
                                                [localRenderer]() {
                                                    std::cout << "[DEBUG] Switching to Rules Screen\n";
                                                    if (UIManager::getInstance()) {
                                                        UIManager::getInstance()->setScreen(std::make_unique<RulesScreen>(localRenderer));
                                                    }
                                                },
                                                m_Font);
    auto optionsButton = std::make_unique<Button>(Config::SCREEN_WIDTH / 2 - Config::MAIN_MENU_BUTTON_WIDTH / 2, 400, Config::MAIN_MENU_BUTTON_WIDTH, Config::MAIN_MENU_BUTTON_HEIGHT,
                                                "Options",
                                                [localRenderer]() {
                                                    std::cout << "[DEBUG] Switching to Options Screen\n";
                                                    if (UIManager::getInstance()) {
                                                        UIManager::getInstance()->setScreen(std::make_unique<OptionsScreen>(localRenderer));
                                                    }
                                                },
                                                m_Font);
    auto exitButton = std::make_unique<Button>(Config::SCREEN_WIDTH / 2 - Config::MAIN_MENU_BUTTON_WIDTH / 2, 500, Config::MAIN_MENU_BUTTON_WIDTH, Config::MAIN_MENU_BUTTON_HEIGHT,
                                                "Exit",
                                                [localRenderer]() {
                                                    std::cout << "[DEBUG] Exiting game\n";
                                                    exit(0);
                                                },
                                                m_Font);

    m_Buttons.push_back(std::move(startButton));
    m_Buttons.push_back(std::move(rulesButton));
    m_Buttons.push_back(std::move(optionsButton));
    m_Buttons.push_back(std::move(exitButton));

    std::cout << "[DEBUG] MainMenuScreen initialized\n";
}

MainMenuScreen::~MainMenuScreen() {
    m_Buttons.clear();

    std::cout << "[DEBUG] MainMenuScreen deleted\n";
}

void MainMenuScreen::handleEvent(SDL_Event& event) {
    for (auto& button : m_Buttons) {
        if (button) {
            button->handleEvent(event);
        }
    }
}

void MainMenuScreen::update() {

}

void MainMenuScreen::render() {
    SDL_SetRenderDrawColor(m_Renderer, 50, 50, 50, 255);
    SDL_RenderClear(m_Renderer);

    for (auto& button : m_Buttons) {
        if (button) {
            button->render(m_Renderer);
        }
    }

    SDL_RenderPresent(m_Renderer);
}
