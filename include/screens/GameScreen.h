#pragma once

#include <vector>
#include <memory>

#include "Screen.h"
#include "game/GameLogic.h"
#include "ui/Button.h"

class GameScreen : public Screen {
    public:
        GameScreen(SDL_Renderer* renderer);
        ~GameScreen();

        void handleEvent(SDL_Event& event) override;
        void update() override;
        void render() override;

    private:
        std::vector<std::unique_ptr<Button>> m_Buttons;
        std::unique_ptr<GameLogic> m_GameLogic;
        Uint32 m_LastUpdateTime;
        TTF_Font* m_Font;
};
