#pragma once

#include <stack>

#include "GameState.h"

class GameStateManager {
    public:
        void pushState(GameState* state);
        void popState();
        void update();
        void render();

    private:
        std::stack<GameState*> stateStack;
};
