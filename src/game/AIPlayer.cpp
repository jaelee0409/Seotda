#include "core/Config.h"
#include "game/AIPlayer.h"
#include "game/Player.h"

AIPlayer::AIPlayer(int id) : Player(id / 2 ? 1000 : 100, id % 2 ? 400 : 100, Config::STARTING_MONEY) {
    m_IsHuman = false;
    m_Name = "AI" + std::to_string(id + 1);
}