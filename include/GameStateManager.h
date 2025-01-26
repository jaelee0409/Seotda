#pragma once

#include <stack>

#include "GameState.h"

enum class GameStateEnum {
    Intro,
    Menu,
    Rules,
    Gameplay
};

class GameStateManager {
    
    public:
        GameStateManager();
        ~GameStateManager();
        
        void pushState(GameState* state);
        void popState();
        void update();
        void render();
        GameStateEnum getCurrentGameState() const;
        void setGameState(GameStateEnum state);

    private:
        std::stack<GameState*> stateStack;
        GameStateEnum m_CurrentGameState;
};
