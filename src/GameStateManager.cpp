#include <stack>

#include "GameStateManager.h"
#include "GameState.h"

GameStateManager::GameStateManager() {

}

GameStateManager::~GameStateManager() {

}

void GameStateManager::pushState(std::unique_ptr<GameState> newState) {
    if (!m_GameStateStack.empty()) {
        m_GameStateStack.top()->exit();
    }
    m_GameStateStack.push(std::move(newState));
    m_GameStateStack.top()->enter();
}

void GameStateManager::popState() {
    if (!m_GameStateStack.empty()) {
        m_GameStateStack.top()->exit();
        m_GameStateStack.pop();
    }
}

void GameStateManager::update() {
    if (!m_GameStateStack.empty()) {
        // m_GameStateStack.top()->update(*this);
    }
}
