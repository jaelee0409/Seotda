#include <iostream>
#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Config.h"
#include "Game.h"
#include "Card.h"

Game::Game() : m_Window(nullptr), m_Renderer(nullptr), m_IsRunning(false), m_Deck(nullptr), m_CurrentGameState(GameStateEnum::Intro) {

}

Game::~Game() {
    
}

bool Game::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "SDL_Image could not initialize! IMG_Error: " << IMG_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1) {
        std::cerr << "SDL_TTF could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        return false;
    }

    m_Window = SDL_CreateWindow("섯다 SEOTDA",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);
    if (m_Window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
    if (m_Renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    m_Deck = std::make_unique<Deck>(m_Renderer);
    loadFaceDownTexture();

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
            if (event.key.keysym.sym == SDLK_d) {  // Example: Deal cards on 'D' key press
                //deck.deal().printCard();
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

    for (const auto& card : m_Deck->getDeck()) {
        card->render();
    }

    SDL_RenderPresent(m_Renderer);
}

bool Game::loadFaceDownTexture() {
    SDL_Texture* faceDownTexture = IMG_LoadTexture(m_Renderer, "assets/images/cards/face_down.png");
    if (faceDownTexture == nullptr) {
        std::cerr << "Failed to load face down card texture: " << IMG_GetError() << std::endl;
        return false;
    }
    Card::setFaceDownTexture(faceDownTexture);
    
    return true;
}

GameStateEnum Game::getCurrentGameState() const {
    return m_CurrentGameState;
}

void Game::setGameState(GameStateEnum state) {
    m_CurrentGameState = state;
}