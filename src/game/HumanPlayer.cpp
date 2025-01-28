#include "HumanPlayer.h"

HumanPlayer::HumanPlayer() {

}

void HumanPlayer::renderHand() {
    for (size_t i = 0; i < hand.size(); ++i) {
        hand[i]->render();
    }
}