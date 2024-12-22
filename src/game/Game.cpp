#include <iostream>

#include "game/Game.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

Game::Game() : window(nullptr), renderer(nullptr), isRunning(false) {}

Game::~Game() {}

bool Game::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    window = SDL_CreateWindow("Seotda Game",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
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

    deck = new Deck(renderer);

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
    if (deck) {
        delete deck;
    }

    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        // TODO: Add event handling for game logic
    }
}

void Game::update() {
    // TODO: Add game state update logic
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);
    SDL_RenderClear(renderer);

    // Render all cards in the deck
    for (const Card& card : deck) {
        card.render(renderer);
    }

    SDL_RenderPresent(renderer);
}
