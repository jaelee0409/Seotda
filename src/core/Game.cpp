#include <iostream>
#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "core/Config.h"
#include "core/Game.h"
#include "game/Card.h"
#include "game/HumanPlayer.h"
#include "game/AIPlayer.h"
#include "game/Player.h"

Game::Game() {

}

Game::~Game() {
    cleanUp();
}

bool Game::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "[ERROR] Game : SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "[ERROR] Game : SDL_Image could not initialize! IMG_Error: " << IMG_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1) {
        std::cerr << "[ERROR] Game : SDL_TTF could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        return false;
    }

    m_Window = SDL_CreateWindow("섯다 SEOTDA",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);
    if (!m_Window) {
        std::cerr << "[ERROR] Game : Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
    if (!m_Renderer) {
        std::cerr << "[ERROR] Game : Renderer could not be created! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    m_FontManager = std::make_unique<FontManager>();
    if (!FontManager::getInstance()->loadFont("Arial24", "fonts/arial.ttf", 24)) {
        return false;
    }
    // if (!FontManager::getInstance()->loadFont("Arial48", "fonts/arial.ttf", 48)) {
    //     return false;
    // }

    m_UIManager = std::make_unique<UIManager>(m_Renderer);

    m_CardTextureManager = std::make_unique<CardTextureManager>(m_Renderer);

    if (!m_CardTextureManager->loadAllTextures()) {
        std::cerr << "[Error] Failed to load card textures!\n";
        return false;
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

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            m_IsRunning = false;
        }
        m_UIManager->handleEvent(event);
    }
}

void Game::update() {
    if (m_UIManager) {
        m_UIManager->update();
    }
}

void Game::render() {
    if (m_UIManager) {
        m_UIManager->render();
    }
}

void Game::cleanUp() {
    if (m_FontManager) {
        m_FontManager.reset();
    }

    if (m_CardTextureManager) {
        m_CardTextureManager->destroyAllTextures();
        m_CardTextureManager.reset();
    }

    if (m_UIManager) {
        m_UIManager.reset();
    }

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
