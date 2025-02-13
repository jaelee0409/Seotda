#include <iostream>
#include <memory>

#include "core/Config.h"
#include "core/UIManager.h"
#include "core/FontManager.h"
#include "screens/GameScreen.h"
#include "screens/MainMenuScreen.h"

GameScreen::GameScreen(SDL_Renderer* renderer) : Screen("GameScreen", renderer), m_LastUpdateTime(SDL_GetTicks()) {
    m_Font = FontManager::getInstance()->getFont("Arial24");
    if (!m_Font) {
        std::cerr << "[ERROR] Font 'Arial24' not found in Font Manager\n";
    }

    try {
        m_GameLogic = std::make_unique<GameLogic>();
        if (!m_GameLogic) {
            throw std::runtime_error("[ERROR] GameLogic creation failed");
        }
        std::cout << "[DEBUG] GameLogic initialized successfully\n";
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Initializing GameScreen: " << e.what() << std::endl;
    }

    auto foldButton = std::make_unique<Button>(800, 600, Config::PLAYER_ACTION_BUTTON_WIDTH, Config::PLAYER_ACTION_BUTTON_HEIGHT,
                                                "Fold",
                                                [this]() {
                                                    if(m_GameLogic->getState() == GameState::BettingRound) {
                                                        std::cout << "[DEBUG] FOLD\n";
                                                        m_GameLogic->onPlayerAction(0, ActionType::Fold, 100);                                                    }
                                                },
                                                m_Font);
    auto checkButton = std::make_unique<Button>(900, 600, Config::PLAYER_ACTION_BUTTON_WIDTH, Config::PLAYER_ACTION_BUTTON_HEIGHT,
                                                "Check",
                                                [this]() {
                                                    if(m_GameLogic->getState() == GameState::BettingRound) {
                                                        std::cout << "[DEBUG] CHECK\n";
                                                        m_GameLogic->onPlayerAction(0, ActionType::Check, 100);
                                                    }
                                                },
                                                m_Font);
    auto callButton = std::make_unique<Button>(1000, 600, Config::PLAYER_ACTION_BUTTON_WIDTH, Config::PLAYER_ACTION_BUTTON_HEIGHT,
                                                "Call",
                                                [this]() {
                                                    if(m_GameLogic->getState() == GameState::BettingRound) {
                                                        std::cout << "[DEBUG] CALL\n";
                                                        m_GameLogic->onPlayerAction(0, ActionType::Call, 100);
                                                    }
                                                },
                                                m_Font);
    auto betButton = std::make_unique<Button>(800, 650, Config::PLAYER_ACTION_BUTTON_WIDTH, Config::PLAYER_ACTION_BUTTON_HEIGHT,
                                                "Bet",
                                                [this]() {
                                                    if(m_GameLogic->getState() == GameState::BettingRound) {
                                                        std::cout << "[DEBUG] BET\n";
                                                        m_GameLogic->onPlayerAction(0, ActionType::Bet, 100);
                                                    }
                                                },
                                                m_Font);
    auto raiseButton = std::make_unique<Button>(900, 650, Config::PLAYER_ACTION_BUTTON_WIDTH, Config::PLAYER_ACTION_BUTTON_HEIGHT,
                                                "Raise",
                                                [this]() {
                                                    if(m_GameLogic->getState() == GameState::BettingRound) {
                                                        std::cout << "[DEBUG] RAISE\n";
                                                        m_GameLogic->onPlayerAction(0, ActionType::Raise, 100);
                                                    }
                                                },
                                                m_Font);
    auto allInButton = std::make_unique<Button>(1000, 650, Config::PLAYER_ACTION_BUTTON_WIDTH, Config::PLAYER_ACTION_BUTTON_HEIGHT,
                                                "All In",
                                                [this]() {
                                                    if(m_GameLogic->getState() == GameState::BettingRound) {
                                                        std::cout << "[DEBUG] ALL IN\n";
                                                        m_GameLogic->onPlayerAction(0, ActionType::AllIn, 100);
                                                    }
                                                },
                                                m_Font);

    m_Buttons.push_back(std::move(foldButton));
    m_Buttons.push_back(std::move(checkButton));
    m_Buttons.push_back(std::move(callButton));
    m_Buttons.push_back(std::move(betButton));
    m_Buttons.push_back(std::move(raiseButton));
    m_Buttons.push_back(std::move(allInButton));

    std::cout << "[DEBUG] GameScreen initialized\n";
}

GameScreen::~GameScreen() {
    m_Buttons.clear();

    std::cout << "[DEBUG] GameScreen deleted\n";
}

void GameScreen::handleEvent(SDL_Event& event) {
    for (auto& button : m_Buttons) {
        if (button) {
            button->handleEvent(event);
        }
    }

    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q) {
            std::cout << "[DEBUG] Returning to Main Menu\n";
            UIManager::getInstance()->setScreen(std::make_unique<MainMenuScreen>(m_Renderer));
        }
        else if (event.key.keysym.sym == SDLK_f) {
            for (auto& player : m_GameLogic->getPlayers()) {
                player.flipHand();
            }
        }
        else if (event.key.keysym.sym == SDLK_r) {
            m_GameLogic->resetRound();
        }
        else if (event.key.keysym.sym == SDLK_d) {
            std::cout << "\n[DEBUG] =============================================================================\n";
            std::cout << "[DEBUG] Current pot: " << m_GameLogic->getPot() << "\n";
            std::cout << "[DEBUG] Current state: " << (int)m_GameLogic->getState() << "\n";
            std::cout << "[DEBUG] Current turn: " << m_GameLogic->getCurrentTurnIndex() << "\n";
            std::cout << "[DEBUG] First to act: " << m_GameLogic->getFirstToActIndex() << "\n";
            std::cout << "[DEBUG] Highest bet: " << m_GameLogic->getHighestBet() << "\n";
            std::cout << "[DEBUG] Last Aggressor: " << m_GameLogic->getLastAggressorIndex() << "\n";
            std::cout << "[DEBUG] Starting player: " << m_GameLogic->getStartingPlayerIndex() << "\n\n";

            int index = 0;
            for (auto& player : m_GameLogic->getPlayers()) {
                std::cout << "[DEBUG] " << player.getName() << "'s bankroll: " << player.getBankroll() << "\n";
                index++;
            }
            std::cout << "[DEBUG] ================================================================================\n\n";
        }
    }
}

void GameScreen::update() {
    Uint32 now = SDL_GetTicks();
    Uint32 deltaTime = now - m_LastUpdateTime;
    m_LastUpdateTime = now;

    m_GameLogic->update(deltaTime);
}

void GameScreen::render() {
    SDL_SetRenderDrawColor(m_Renderer, 0, 128, 0, 255);
    SDL_RenderClear(m_Renderer);

    m_GameLogic->getDeck().render(m_Renderer);
    for (auto& player : m_GameLogic->getPlayers()) {
        player.renderHand(m_Renderer);
    }

    for (auto& button : m_Buttons) {
        if (button) {
            button->render(m_Renderer);
        }
    }
    

    SDL_RenderPresent(m_Renderer);
}
