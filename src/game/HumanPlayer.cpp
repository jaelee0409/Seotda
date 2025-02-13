#include "core/Config.h"
#include "game/HumanPlayer.h"
#include "game/Player.h"

HumanPlayer::HumanPlayer() : Player(Config::SCREEN_WIDTH / 2 - Config::CARD_WIDTH / 2, 600, Config::STARTING_MONEY) {
    m_IsHuman = true;
    m_Name = "Me";
}
