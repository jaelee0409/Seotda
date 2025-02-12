#pragma once

#include <stack>
#include <memory>

#include "GameState.h"

/**
 * @class GameStateManager
 * @brief Manages transitions between different game states.
 */
class GameStateManager {
    
    public:
        GameStateManager();
        ~GameStateManager();
        
        void pushState(std::unique_ptr<GameState> newState);
        void popState();
        void update();

    private:
    std::stack<std::unique_ptr<GameState>> m_GameStateStack;
};
