#include <stack>

#include "GameStateManager.h"
#include "GameState.h"

GameStateManager::GameStateManager() : m_CurrentGameState(GameStateEnum::Gameplay) {

}

GameStateManager::~GameStateManager() {

}

void GameStateManager::pushState(GameState* state) {
    if (!stateStack.empty()) {
        stateStack.top()->exit();
    }
    stateStack.push(state);
    state->enter();
}

void GameStateManager::popState() {
    if (!stateStack.empty()) {
        stateStack.top()->exit();
        delete stateStack.top();
        stateStack.pop();
    }
    if (!stateStack.empty()) {
        stateStack.top()->enter();
    }
}

void GameStateManager::update() {
    if (!stateStack.empty()) {
        stateStack.top()->update();
    }
}

void GameStateManager::render() {
    if (!stateStack.empty()) {
        stateStack.top()->render();
    }
}

GameStateEnum GameStateManager::getCurrentGameState() const {
    return m_CurrentGameState;
}

void GameStateManager::setGameState(GameStateEnum state) {
    m_CurrentGameState = state;
}