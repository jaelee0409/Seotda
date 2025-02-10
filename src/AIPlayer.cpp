#include "AIPlayer.h"

AIPlayer::AIPlayer(int id) : Player(id / 2 ? 1000 : 100, id % 2 ? 400 : 100) {

}