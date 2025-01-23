#include <iostream>
#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Config.h"
#include "game/Game.h"

Game::Game() : window(nullptr), renderer(nullptr), isRunning(false), deck(nullptr) {}

Game::~Game() {}

bool Game::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "SDL_image could not initialize! IMG Error: " << IMG_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1) {
        std::cerr << "TTF could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Seotda Game",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);

    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    if (renderer == nullptr) {
        std::cerr << "Renderer is null. Check SDL_Renderer initialization." << std::endl;
    }

    deck = std::make_unique<Deck>(renderer);

    isRunning = true;

    return true;
}

void Game::run() {
    while (isRunning) {
        handleEvents();
        update();
        render();
    }
}

void Game::cleanUp() {
    IMG_Quit();

    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_Quit();
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
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
    switch (currentState) {
        case GameState::WaitingForInput:
            // Handle input and game logic
            break;
        case GameState::PlayerTurn:
            // Handle player's turn
            break;
        case GameState::RoundEnded:
            // End round and prepare for next round
            break;
        case GameState::GameOver:
            // Handle game over logic
            break;
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);
    SDL_RenderClear(renderer);

    // for (const auto& card : deck->getDeck()) {
    //     card.render();
    // }

    
    for (const auto& card : deck->getDeck()) {
        card->render();
    }

    SDL_RenderPresent(renderer);
}
