#pragma once

#include "GameState.h"

class IntroState : public GameState {
    public:
        void enter() override;
        void exit() override;
        void update() override;
        void render() override;
};