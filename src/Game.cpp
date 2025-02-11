#include <iostream>
#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Config.h"
#include "Game.h"
#include "Card.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "Player.h"

GameStateManager Game::s_GameStateManager;

Game::Game() : m_Window(nullptr), m_Renderer(nullptr), m_IsRunning(false), m_Pot(0) {

}

Game::~Game() {
    
}

GameStateManager& Game::getGameStateManager() {
    return s_GameStateManager;
}

bool Game::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "[Game::initialize] SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "[Game::initialize] SDL_Image could not initialize! IMG_Error: " << IMG_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1) {
        std::cerr << "[Game::initialize] SDL_TTF could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        return false;
    }

    m_Window = SDL_CreateWindow("섯다 SEOTDA",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);
    if (m_Window == nullptr) {
        std::cerr << "[Game::initialize] Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
    if (m_Renderer == nullptr) {
        std::cerr << "[Game::initialize] Renderer could not be created! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    // Load face down card texture
    if (!Card::loadFaceDownTexture(m_Renderer)) {
        std::cerr << "[Game::initialize] Failed to load face-down card texture." << std::endl;
        return false;
    }

    if (!Chip::loadChipTextures(m_Renderer)) {
        std::cerr << "[Game::initialize] Failed to load chip textures!" << std::endl;
        return false;
    }

    // Initialize the deck
    m_Deck.initializeDeck(m_Renderer);

    // Initialize players
    m_Players.push_back(std::make_unique<HumanPlayer>());

    // Create 4 AI players and add them to the players vector
    for (int i = 0; i < 4; ++i) {
        m_Players.push_back(std::make_unique<AIPlayer>(i));
    }

    return true;
}

void Game::run() {
    m_IsRunning = true;

    while (m_IsRunning) {
        handleEvents();
        update();
        render();
    }
}

void Game::cleanUp() {
    m_Players.clear();

    Chip::destroyChipTextures();
    Card::destroyFaceDownTexture();

    TTF_Quit();
    IMG_Quit();

    if (m_Renderer) {
        SDL_DestroyRenderer(m_Renderer);
        m_Renderer = nullptr;
    }
    if (m_Window) {
        SDL_DestroyWindow(m_Window);
        m_Window = nullptr;
    }

    SDL_Quit();
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            m_IsRunning = false;
        }
        else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_d) {
                dealCards();
            }
            // Debugging purpose
            else if (event.key.keysym.sym == SDLK_f) {
                for (auto& player : m_Players) {
                    player->flipHand();
                }
            }
            else if (event.key.keysym.sym == SDLK_r) {
                static bool isResetting = false;

                if (isResetting) {
                    std::cerr << "[DEBUG] Reset already in progress, ignoring extra presses." << std::endl;
                    return;
                }
            
                isResetting = true;

                std::cerr << "[DEBUG] Resetting deck..." << std::endl;
                for (auto& player : m_Players) {
                    std::cerr << "[DEBUG] Clearing " << typeid(*player).name() << "'s hand..." << std::endl;
                    player->resetHand();
                }
                m_Deck.reshuffle();
                std::cerr << "[DEBUG] Deck reshuffled successfully. 1" << std::endl;

                resetPot();

                isResetting = false;
            }
            else if (event.key.keysym.sym == SDLK_b) {
                collectBet(m_Players[0].get(), 500);
            }
            else if (event.key.keysym.sym == SDLK_p) {
                addToPot(1500000);
            }
        }
    }
}

void Game::update() {
    for (auto& player : m_Players) {
        auto& hand = player->getHand();
        if (hand.first)
            hand.first->update();
        if (hand.second)
            hand.second->update();
    }
    // switch (currentState) {
    //     case GameState::WaitingForInput:
    //         // Handle input and game logic
    //         break;
    //     case GameState::PlayerTurn:
    //         // Handle player's turn
    //         break;
    //     case GameState::RoundEnded:
    //         // End round and prepare for next round
    //         break;
    //     case GameState::GameOver:
    //         // Handle game over logic
    //         break;
    // }
}

void Game::render() {
    SDL_SetRenderDrawColor(m_Renderer, 0, 128, 0, 255);
    SDL_RenderClear(m_Renderer);

    if (s_GameStateManager.getCurrentGameState() == GameStateEnum::Gameplay) {
        for (const auto& card : m_Deck.getDeck()) {
            card->render();
        }
        for (const auto& player : m_Players) {
            if (player->hasHand()) { // Ensure at least one card exists
                player->renderHand();
                
            }
            player->renderChips(m_Renderer);
        }
    
        renderPotChips();
    }
    
    SDL_RenderPresent(m_Renderer);
}

void startGame() {

}
        
/**
 * @brief Deals two cards from the deck to each player's hand and start moving them. Human player's hand is dealt face up.
 */
void Game::dealCards() {
    for (auto& player : m_Players) {
        if (player->hasHand()) {
            std::cerr << "[Game::dealCards] Cards are already dealt. Cannot redeal!" << std::endl;
            return;
        }

        SDL_Rect target1 = player->getPosition();
        SDL_Rect target2 = { target1.x + 50, target1.y, Config::CARD_WIDTH, Config::CARD_HEIGHT };

        std::unique_ptr<Card> card1 = m_Deck.deal();
        std::unique_ptr<Card> card2 = m_Deck.deal();

        if (!card1 || !card2) {
            std::cerr << "[Game::dealCards] Not enough cards to deal!" << std::endl;
            return;
        }

        card1->startMoving(target1, 500);
        card2->startMoving(target2, 500);

        if (dynamic_cast<HumanPlayer*>(player.get()) != nullptr) {
            card1->flip();
            card2->flip();
        }

        player->addCardToHand(std::move(card1));
        player->addCardToHand(std::move(card2));
    }
}

void bettingPhase() {

}

void evaluateHands() {

}

void nextRound() {

}

void Game::addToPot(int amount) {
    std::vector<int> chipValues = { 1000000, 500000, 100000, 50000, 10000 };

    for (int chip : chipValues) {
        while (amount >= chip) {
            m_PotChips[chip]++;
            amount -= chip;
        }
    }

    std::cerr << "[Game::addToPot] Added " << amount << " to pot. New pot size: " << m_PotChips.size() << " chip types." << std::endl;
}

void Game::collectBet(Player* player, int amount) {
    // if (player->placeBet(amount)) {
    //     m_Pot += amount;
    //     std::cerr << "[Game] Bet collected: " << amount << " | Pot Total: " << m_Pot << std::endl;
    // }
}

void Game::resetPot() {
    m_PotChips.clear();
}

void Game::renderPotChips() const {
    int x = Config::SCREEN_WIDTH / 2;  // Center pot on screen
    int y = Config::SCREEN_HEIGHT / 2 + 100;

    for (const auto& [chipValue, count] : m_PotChips) {
        for (int i = 0; i < count; ++i) {
            if (i >= 10)
                break;
            SDL_Rect chipRect = { x, y - (i * 5), 40, 40 };
            SDL_RenderCopy(m_Renderer, Chip::getTextureForValue(chipValue), nullptr, &chipRect);
        }
        x += 40;
    }
}