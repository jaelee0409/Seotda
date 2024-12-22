#include "game.h"

int main(int argc, char* argv[]) {
    Game game;

    if (!game.initialize()) {
        return 1;
    }

    game.run();
    game.cleanUp();

    return 0;
}