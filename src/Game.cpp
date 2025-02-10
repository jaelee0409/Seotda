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

Game::Game() : m_Window(nullptr), m_Renderer(nullptr), m_IsRunning(false) {

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

    Card::destroyFaceDownTexture();

    if (m_Renderer) {
        SDL_DestroyRenderer(m_Renderer);
        m_Renderer = nullptr;
    }
    if (m_Window) {
        SDL_DestroyWindow(m_Window);
        m_Window = nullptr;
    }
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            m_IsRunning = false;
        }
        else if (event.type == SDL_KEYDOWN) {
            // Handle key presses for game actions (deal cards, player input)
            if (event.key.keysym.sym == SDLK_d) {
                dealCards();
            }
            else if (event.key.keysym.sym == SDLK_f) {
                for (auto& player : m_Players) {
                    player->flipHand();
                }
            }
            else if (event.key.keysym.sym == SDLK_r) {
                m_Deck.reshuffle();

                for (auto& player : m_Players) {
                    player->resetHand();
                }
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
        for (auto& player : m_Players) {
            if (player->getHand().first || player->getHand().second) { // Ensure at least one card exists
                player->renderHand();
            }
        }
    }
    
    SDL_RenderPresent(m_Renderer);
}

void startGame() {

}
        

void Game::dealCards() {
    for (auto& player : m_Players) {
        if (player->hasHand()) {
            std::cerr << "[Game::dealCards] Cards are already dealt. Cannot redeal!" << std::endl;
            return;  // Prevent dealing if hands are already full
        }
    }

    for (auto& player : m_Players) {
        SDL_Rect target1 = player->getPosition();
        SDL_Rect target2 = { target1.x + 50, target1.y, Config::CARD_WIDTH, Config::CARD_HEIGHT };

        std::unique_ptr<Card> card1 = m_Deck.deal();
        std::unique_ptr<Card> card2 = m_Deck.deal();

        if (card1 && card2) {
            card1->startMoving(target1, 500);
            card2->startMoving(target2, 500);

            if (dynamic_cast<HumanPlayer*>(player.get()) != nullptr) {
                card1->flip();
                card2->flip();
            }

            player->addCardToHand(std::move(card1));
            player->addCardToHand(std::move(card2));
        }
        else {
            std::cerr << "[Game::dealCards] Not enough cards to deal!" << std::endl;
        }
    }
}

void bettingPhase() {

}

void evaluateHands() {

}

void nextRound() {

}