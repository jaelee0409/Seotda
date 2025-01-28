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

Game::Game() : m_Window(nullptr), m_Renderer(nullptr), m_IsRunning(false), m_Deck(nullptr) {

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

    // Create the deck
    m_Deck.initializeDeck(m_Renderer);
    if (!Deck::loadFaceDownTexture(m_Renderer)) {
        std::cerr << "[Game::initialize] Deck could not load face down card texture! : " << SDL_GetError() << "\n";
        return false;
    }

    // Initialize players
    HumanPlayer* humanPlayer = new HumanPlayer();
    players.push_back(humanPlayer);

    // Create 4 AI players and add them to the players vector
    for (int i = 0; i < 4; ++i) {
        AIPlayer* aiPlayer = new AIPlayer();
        players.push_back(aiPlayer);
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
    for (Player* player : players) {
            delete player;
    }

    Deck::destroyFaceDownTexture();

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
            if (event.key.keysym.sym == SDLK_d) {  // Example: Deal cards on 'D' key press
                dealCard();
            }
        }
    }
}

void Game::update() {
    
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
            card.render();
        }
        for (size_t i = 0; i < players.size(); ++i) {
            players[i]->renderHand();
        }
    }
    
    SDL_RenderPresent(m_Renderer);
}

void Game::dealCard() {
    Card* dealtCard1 = &m_Deck.back();
    //Card dealtCard2 = m_Deck.deal();
    players[0]->addCardToHand(dealtCard1);
    //players[0]->addCardToHand(dealtCard2);
    players[0]->flipCardInHand(0);
    SDL_Rect playerHandPosition;
    playerHandPosition.x = 0;
    playerHandPosition.y = 0;
    //m_Deck.animateDealCard(dealtCard1, playerHandPosition, 0.1f);
}