#include <iostream>

#include "game/AIHelper.h"

/**
 * @brief Returns a random action: Fold, Check, Call, Bet, Raise, or All In.
 *        This is for debugging. This is a placeholder AI.
 */
ActionType getRandomAIAction() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 5);

    int roll = dist(gen);
    switch (roll) {
        case 0:
            return ActionType::Fold;
        case 1:
            return ActionType::Check;
        case 2:
            return ActionType::Call;
        case 3:
            return ActionType::Bet;
        case 4:
            return ActionType::Raise;
        case 5:
            return ActionType::AllIn;
    }
    // fallback
    return ActionType::Fold;
}
