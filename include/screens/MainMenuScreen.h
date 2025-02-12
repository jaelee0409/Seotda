#pragma once

#include <vector>
#include <memory>

#include "screens/Screen.h"
#include "ui/Button.h"

class MainMenuScreen : public Screen {
    public:
        MainMenuScreen(SDL_Renderer* renderer);
        ~MainMenuScreen();

        void handleEvent(SDL_Event& event) override;
        void update() override;
        void render() override;
    private:
        std::vector<std::unique_ptr<Button>> m_Buttons;
        TTF_Font* m_Font;
};
