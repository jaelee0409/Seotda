#include "GameplayState.h"

GameplayState::GameplayState() : currentPhase(GamePhaseEnum::IDLE) {

}

void GameplayState::enter() {
    switchToPhase(currentPhase);
}
void GameplayState::exit() {
    // Clean up intro resources (e.g., stop music)
}
void GameplayState::update() {
    switch (currentPhase) {
        case GamePhaseEnum::IDLE:
            // Handle gameplay round logic here
            break;
        case GamePhaseEnum::DEALING:
            // Handle card dealing logic here
            break;
        case GamePhaseEnum::BETTING:
            // Handle betting logic here
            break;
        case GamePhaseEnum::SHOW_WINNER:
            // Show the winner and reset for next round
            break;
    }
}
void GameplayState::render() {
    switch (currentPhase) {
        case GamePhaseEnum::IDLE:
            // Handle gameplay round logic here
            break;
        case GamePhaseEnum::DEALING:
            // Handle card dealing logic here
            break;
        case GamePhaseEnum::BETTING:
            // Handle betting logic here
            break;
        case GamePhaseEnum::SHOW_WINNER:
            // Show the winner and reset for next round
            break;
    }
}

void GameplayState::transitionToNextPhase() {
    // Transition to the next phase in the game
    switch (currentPhase) {
        case GamePhaseEnum::IDLE:
            currentPhase = GamePhaseEnum::DEALING;
            break;
        case GamePhaseEnum::DEALING:
            currentPhase = GamePhaseEnum::BETTING;
            break;
        case GamePhaseEnum::BETTING:
            currentPhase = GamePhaseEnum::SHOW_WINNER;
            break;
        case GamePhaseEnum::SHOW_WINNER:
            // Reset or go back to main menu
            break;
    }
    switchToPhase(currentPhase);
}

void GameplayState::switchToPhase(GamePhaseEnum phase) {
    // switch (phase) {
    //     case GamePhase::IDLE:
    //         // Switch to dealing state
    //         gamePhaseStateManager.pushState(std::make_unique<IdleState>());
    //         break;
    //     case GamePhase::DEALING:
    //         // Switch to betting state
    //         gamePhaseStateManager.pushState(std::make_unique<DealingState>());
    //         break;
    //     case GamePhase::BETTING:
    //         // Switch to round state
    //         gamePhaseStateManager.pushState(std::make_unique<BettingState>());
    //         break;
    //     case GamePhase::SHOW_WINNER:
    //         // Switch to winner state
    //         gamePhaseStateManager.pushState(std::make_unique<ShowWinnerState>());
    //         break;
    // }
}