#include <iostream>

#include "core/Config.h"
#include "game/GameLogic.h"
#include "game/HumanPlayer.h"
#include "game/AIPlayer.h"
#include "game/AIHelper.h"

GameLogic::GameLogic() {
    m_Deck.initializeDeck();
    m_Players.emplace_back(HumanPlayer());
    for (int i = 0; i < 4; ++i) {
        m_Players.emplace_back(AIPlayer(i));
    }

    setState(GameState::DealingCards);

    std::cout << "[DEBUG] GameLogic Initialized\n";
}

void GameLogic::resetGame() {
    for (auto& player : m_Players) {
        player.resetHand();
        player.resetBet();
    }
    m_Deck.reshuffle();
    resetPot();
    m_StartingPlayerIndex = 0;

    // TODO

    std::cout << "[DEBUG] New game\n";
}

void GameLogic::resetRound() {
    for (auto& player : m_Players) {
        player.resetHand();
        player.resetBet();
    }
    m_Deck.reshuffle();
    resetPot();
    resetHighestBet();
    m_CurrentTurnIndex = m_StartingPlayerIndex;

    std::cout << "[DEBUG] New round\n";
}

/*
  ==============================================================================
    Dealing
  ==============================================================================
*/
void GameLogic::dealCards() {
    if (m_Players.empty()) {
        std::cerr << "[Error] No players to deal cards to\n";
        return;
    }

    if (m_Players[0].getBankroll() == 0) {
        setState(GameState::LostGame);
        return;
    }

    for (auto& player : m_Players) {
        if(player.hasHand())
            return;
        
        Card c1 = m_Deck.deal();
        Card c2 = m_Deck.deal();

        player.addCardToHand(c1);
        player.addCardToHand(c2);

        if (player.getIsHuman()) {
            player.flipHand();
        }
    }
}

// void GameLogic::startDealing() {
//     m_DealSequence.clear();
//     m_DealIndex = 0;

//     for (int round = 0; round < 2; ++round) {
//         for (int playerIndex = 0; playerIndex < m_Players.size(); ++playerIndex) {
//             Card c = m_Deck.deal(); 

//             DealEvent dealEvent;
//             dealEvent.playerIndex = playerIndex;
//             dealEvent.card = c;
//             dealEvent.finished = false;
//             m_DealSequence.push_back(dealEvent);
//         }
//     }

//     // Switch to DealingCards state, set a time limit if you want
//     setState(GameState::DealingCards);
// }


/*
  ==============================================================================
    Betting system
  ==============================================================================
*/
void GameLogic::startBettingRound() {
    m_FirstToActIndex = m_CurrentTurnIndex;  
    m_LastAggressorIndex = -1;
    setState(GameState::BettingRound);
}

// void GameLogic::addToPot(int amount) {
//     std::vector<int> chipValues = {1000000, 500000, 100000, 50000, 10000};

//     for (int chip : chipValues) {
//         while (amount >= chip) {
//             m_PotChips[chip]++;
//             amount -= chip;
//         }
//     }

//     std::cout << "[DEBUG] Added to pot: " << amount << "\n";
// }

void GameLogic::collectBetsToPot() {
    for (auto& player : m_Players) {
        m_Pot += player.getCurrentBet();
        player.resetBet();
    }
    std::cout << "[DEBUG] Collected bets. Pot is now: " << m_Pot << "\n";
}

void GameLogic::resetPot() {
    m_Pot = 0;
    std::cout << "[DEBUG] Resetting the pot\n";
}

void GameLogic::resetHighestBet() {
    m_HighestBet = 0;
    std::cout << "[DEBUG] Resetting the highest bet\n";
}

void GameLogic::distributePotToWinner(int winnerIndex) {
    m_Players[winnerIndex].addWinnings(m_Pot);
    m_Pot = 0;
    std::cout << "[DEBUG] Player " << winnerIndex << " wins pot of " << m_Pot << "\n";
}

void GameLogic::endRound() {
    // Distribute pot, reset hands, etc.
    // Next time, the next player in line starts
    m_StartingPlayerIndex = (m_StartingPlayerIndex + 1) % m_Players.size();
    std::cout << "[DEBUG] Round ended. Next round will start with Player "
              << m_StartingPlayerIndex << "\n";
}

/*
  ==============================================================================
    Turns
  ==============================================================================
*/
void GameLogic::update(Uint32 deltaTime) {
    switch (m_CurrentState) {
        case GameState::DealingCards:
            handleDealing(deltaTime);
            break;
        case GameState::BettingRound:
            handleBetting(deltaTime);
            break;
        case GameState::Showdown:
            handleShowdown(deltaTime);
            break;
        case GameState::LostGame:
            handleLostGame(deltaTime);
            break;
    }
}

void GameLogic::handleDealing(Uint32 dt) {
    if (m_TimeLeft > dt) {
        m_TimeLeft -= dt;
    } else {
        m_TimeLeft = 0;
    }

    if (m_TimeLeft == 0) {
        dealCards();
        startBettingRound();
        return;
    }

}

void GameLogic::handleBetting(Uint32 dt) {
    // This function is called every frame while we are in BettingRound
    // Possibly track a timer if you want to auto-fold on timeout
    if (m_CurrentTurnIndex != 0) { // e.g. 0 = human, 1..4 = AI
        // Decide a random action
        ActionType action = getRandomAIAction();

        // Then call onPlayerAction
        onPlayerAction(m_CurrentTurnIndex, action, 100);
    }

    // If everyone has called or folded except one, we end the betting
    // Example check: if we've reached some condition, do collectBetsToPot(), setState(Showdown)
    // if (checkBettingRoundEnd()) {
    //     collectBetsToPot();
    //     setState(GameState::Showdown);
    // }
}

void GameLogic::handleShowdown(Uint32 dt) {
    // Show results
    if (m_TimeLeft > dt) {
        m_TimeLeft -= dt;
    } else {
        m_TimeLeft = 0;
    }

    if (m_TimeLeft == 0) {
        // end round, or go back to dealing
        //int winnerIndex = findWinnerIndex();
        //distributePotToWinner(winnerIndex);
        resetRound();
        setState(GameState::DealingCards);
    }
}

void GameLogic::handleLostGame(Uint32 dt) {

}

void GameLogic::onPlayerAction(int playerIndex, ActionType action, int amount) {
    if (m_CurrentState != GameState::BettingRound) {
        return;
    }

    if (playerIndex != m_CurrentTurnIndex) {
        std::cerr << "[ERROR] It's not player " << playerIndex << "'s turn\n";
        return;
    }

    // If the action is invalid, don't pass the turn
    if (!isActionValid(playerIndex, action, amount)) {
        std::cerr << "[ERROR] Invalid action\n";
        return;
    }

    switch (action) {
        case ActionType::Fold:
            handleFold(playerIndex);
            break;
        case ActionType::Check:
            handleCheck(playerIndex);
            break;
        case ActionType::Call:
            handleCall(playerIndex);
            break;
        case ActionType::Bet:
            handleBet(playerIndex, amount);
            break;
        case ActionType::Raise:
            handleRaise(playerIndex, amount);
            break;
        case ActionType::AllIn:
            handleAllIn(playerIndex);
            break;
    }

    // after performing the action, move to the next player's turn
    checkBettingRoundEnd();
    nextPlayerTurn();
}

bool GameLogic::isActionValid(int playerIndex, ActionType action, int amount) {
    Player& player = m_Players[playerIndex];

    // 1) If the player is folded or all-in already, no further action
    if (player.getIsFolded()) {
        std::cerr << "[ERROR] Player already folded\n";
        return false;
    }
    if (player.getIsAllIn()) {
        std::cerr << "[ERROR] Player is already all in\n";
        return false;
    }

    int neededToCall = m_HighestBet - player.getCurrentBet();
    if (neededToCall < 0)
        neededToCall = 0;

    switch (action) {
        case ActionType::Check:
            if (neededToCall != 0) {
                return false;
            }
            break;

        case ActionType::Call:
            // Call is only valid if neededToCall > 0
            if (neededToCall <= 0) {
                return false;
            }
            // Also ensure the player has enough bankroll 
            if (player.getBankroll() < neededToCall) {
                // Might auto-all-in instead, so up to you if you treat that as invalid
                return false;
            }
            break;

        case ActionType::Bet:
            // Bet only valid if m_HighestBet == 0
            if (m_HighestBet != 0) {
                return false;
            }
            // amount must be > 0, and <= player.getBankroll()
            if (amount <= 0 || amount > player.getBankroll()) {
                return false;
            }
            break;

        case ActionType::Raise:
            // Raise only valid if m_HighestBet > 0
            if (m_HighestBet == 0) {
                return false;
            }
            // amount must be > 0, etc.
            if (amount <= 0 || (player.getBankroll() < (amount + neededToCall))) {
                return false;
            }
            break;

        case ActionType::AllIn:
            // AllIn is always valid if they have some bankroll left, but you can define constraints
            if (player.getBankroll() == 0) {
                return false;
            }
            break;

        case ActionType::Fold:
            // Usually valid any time if they're not folded
            break;
        }

    return true; // If none of the checks failed
}

int GameLogic::countActivePlayers() {
    int count = 0;
    for (int i = 0; i < m_Players.size(); ++i) {
        if (!m_Players[i].getIsFolded()) {
            count++;
        }
    }
    return count;
}

void GameLogic::checkBettingRoundEnd() {
    int activePlayers = 0;
    int lastActiveIndex = -1;
    for (int i = 0; i < m_Players.size(); ++i) {
        if (!m_Players[i].getIsFolded()) {
            activePlayers++;
            lastActiveIndex = i;
        }
    }

    if (activePlayers == 1) {
        std::cout << "[DEBUG] Player " << m_CurrentTurnIndex << " wins. Everyone else folded\n";
        // Everyone else folded => immediate end of round
        distributePotToWinner(lastActiveIndex);
        setState(GameState::Showdown); // or skip to next round
        return;
    }

    // 2) Check if all active players have matched m_HighestBet
    // i.e. for each not folded, (getCurrentBet() == m_HighestBet)
    bool allMatched = true;
    for (int i = 0; i < m_Players.size(); ++i) {
        if (!m_Players[i].getIsFolded()) {
            if (m_Players[i].getCurrentBet() < m_HighestBet) {
                allMatched = false;
                break;
            }
        }
    }

    if (allMatched) {
        std::cout << "[DEBUG] Everyone matched the bet\n";
        collectBetsToPot();
        setState(GameState::Showdown);
    }
}

void GameLogic::handleFold(int playerIndex) {
    Player& player = m_Players[playerIndex];
    player.setIsFolded(true);

    std::cout << "[DEBUG] Player " << playerIndex << " folds\n";
}

void GameLogic::handleCheck(int playerIndex) {
    Player& player = m_Players[playerIndex];
    int neededToCall = m_HighestBet - player.getCurrentBet();

    // The check button should be disabled but I am adding this check just in case
    if (neededToCall > 0) {
        std::cerr << "[ERROR] Player " << playerIndex 
                  << " can't check; Needs at least " << neededToCall << " to call\n";
        return;
    }

    std::cout << "[DEBUG] Player " << playerIndex << " checks\n";
}

void GameLogic::handleCall(int playerIndex) {
    Player& player = m_Players[playerIndex];
    int neededToCall = m_HighestBet - player.getCurrentBet();

    if (neededToCall <= 0) {
        // If there's nothing to call, a "call" is effectively a check
        std::cout << "[DEBUG] Player " << playerIndex << " checks (no call needed).\n";
        return;
    }

    // Attempt to place the bet for neededToCall
    if (!player.placeBet(neededToCall)) {
        // Not enough bankroll => possibly force all-in or fold
        // For now, auto-all-in if partial
        int leftover = player.getBankroll(); // what's left
        if (leftover > 0) {
            // go all-in
            handleAllIn(playerIndex);
        } else {
            // can't bet anything => fold
            handleFold(playerIndex);
        }
        return;
    }

    std::cout << "[DEBUG] " << player.getName() << " calls\n";
}

void GameLogic::handleBet(int playerIndex, int betAmount) {
    if (m_HighestBet != 0) {
        std::cerr << "[ERROR] handleBet called, but highest bet is already > 0, so this is actually a raise.\n";
        return;
    }

    Player& player = m_Players[playerIndex];
    if (!player.placeBet(betAmount)) {
        // if not enough bankroll, maybe auto-all-in
        handleAllIn(playerIndex);
        return;
    }
    m_HighestBet = player.getCurrentBet();
    m_LastAggressorIndex = playerIndex;
    std::cout << "[DEBUG] " << player.getName() << " bets " << betAmount << ". Highest bet = " << m_HighestBet << "\n";
}

void GameLogic::handleRaise(int playerIndex, int raiseAmount) {
    Player& player = m_Players[playerIndex];
    int neededToCall = m_HighestBet - player.getCurrentBet();
    if (neededToCall < 0) neededToCall = 0;

    int totalBetThisAction = neededToCall + raiseAmount;
    if (!player.placeBet(totalBetThisAction)) {
        handleAllIn(playerIndex);
        return;
    }

    int newTotalBet = player.getCurrentBet();
    if (newTotalBet > m_HighestBet) {
        m_HighestBet = newTotalBet;
        m_LastAggressorIndex = playerIndex;
        std::cout << "[DEBUG] " << player.getName() << " raises to " << newTotalBet << "\n";
    } else {
        std::cout << "[DEBUG] " << player.getName() << " tried to raise but only matched the call\n";
    }
}

void GameLogic::handleAllIn(int playerIndex) {
    Player& player = m_Players[playerIndex];
    int leftover = player.getBankroll(); // how much they can still bet

    if (leftover <= 0) {
        // They have no money => effectively a check/call if they've matched or a fold if not
        std::cerr << "[ERROR] " << player.getName() << " has no bankroll for all-in, ignoring\n";
        return;
    }

    // All in => bet their entire bankroll
    player.placeBet(leftover);

    int newTotalBet = player.getCurrentBet();
    if (newTotalBet > m_HighestBet) {
        m_HighestBet = newTotalBet;
        std::cout << "[DEBUG] " << player.getName() << " goes ALL IN. New highest bet is " << m_HighestBet << "\n";
    } else {
        std::cout << "[DEBUG] " << player.getName() << " goes ALL IN for " 
                  << leftover << ", total bet " << newTotalBet << ".\n";
    }

    std::cout << "[DEBUG] " << player.getName() << " all ins\n";
}

void GameLogic::nextPlayerTurn() {
    do {
        m_CurrentTurnIndex = (m_CurrentTurnIndex + 1) % m_Players.size();
    } while (m_Players[m_CurrentTurnIndex].getIsFolded());
}


/*
  ==============================================================================
    Getters
  ==============================================================================
*/
GameState GameLogic::getState() const {
    return m_CurrentState;
}

int GameLogic::getPot() const {
    return m_Pot;
}

int GameLogic::getStartingPlayerIndex() const {
    return m_StartingPlayerIndex;

}
int GameLogic::getCurrentTurnIndex() const {
    return m_CurrentTurnIndex;
}

int GameLogic::getHighestBet() const {
    return m_HighestBet;
}

int GameLogic::getFirstToActIndex() const {
    return m_FirstToActIndex;
}

int GameLogic::getLastAggressorIndex() const {
    return m_LastAggressorIndex;
}

int GameLogic::getBankroll(int playerIndex) const {
    return m_Players[playerIndex].getBankroll();
}

Deck& GameLogic::getDeck() {
    return m_Deck;
}

std::vector<Player>& GameLogic::getPlayers() {
    return m_Players;
}

/*
  ==============================================================================
    Setters
  ==============================================================================
*/
void GameLogic::setState(GameState newState) {
    m_CurrentState = newState;
    switch (newState) {
        case GameState::DealingCards:
            m_TimeLeft = 2000;  // 2 seconds
            // maybe also shuffle deck or deal here
            std::cout << "[DEBUG] Dealing cards\n";
            break;
        case GameState::BettingRound:
            std::cout << "[DEBUG] Betting round\n";
            break;
        case GameState::Showdown:
            m_TimeLeft = 2000;  // show results for 2 seconds
            std::cout << "[DEBUG] Showdown\n";
            break;
        case GameState::LostGame:
            m_TimeLeft = 2000;  // show results for 2 seconds
            std::cout << "[DEBUG] You have no money to play\n";
            break;
    }
}