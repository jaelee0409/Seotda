#pragma once

#include "GameState.h"
#include "GameStateManager.h"

class GameplayState : public GameState {
    public:
        enum class GamePhaseEnum {
            IDLE,
            DEALING,
            BETTING,
            SHOW_WINNER
        };

        GameplayState();
        
        void enter() override;
        void exit() override;
        void update() override;
        void render() override;

        void transitionToNextPhase();
        void switchToPhase(GamePhaseEnum phase);

    private:
        GamePhaseEnum currentPhase;
        GameStateManager gamePhaseStateManager;
};