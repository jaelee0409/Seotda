#include <iostream>

#include "core/Config.h"
#include "game/GameLogic.h"
#include "game/HumanPlayer.h"
#include "game/AIPlayer.h"

GameLogic::GameLogic() {
    m_Deck.initializeDeck();
    m_CurrentPlayerIndex = 0;

    m_Players.emplace_back(HumanPlayer());

    for (int i = 0; i < 4; ++i) {
        m_Players.emplace_back(AIPlayer(i));
    }

    setState(GameState::DealingCards);

    std::cout << "[DEBUG] GameLogic Initialized\n";
}

void GameLogic::update(Uint32 deltaTime) {
    switch (m_CurrentState) {
        case GameState::DealingCards:
            handleDealing(deltaTime);
            break;
        case GameState::PlayerTurn:
            handlePlayerTurn(deltaTime);
            break;
        case GameState::AITurn:
            handleAITurn(deltaTime);
            break;
        case GameState::Showdown:
            handleShowdown(deltaTime);
            break;
        }
}

void GameLogic::resetGame() {
    for (auto& player : m_Players) {
        player.resetHand();
    }
    m_Deck.reshuffle();
    resetPot();
    m_CurrentPlayerIndex = 0;

    // TODO

    std::cout << "[DEBUG] New game\n";
}

void GameLogic::resetRound() {
    for (auto& player : m_Players) {
        player.resetHand();
    }
    m_Deck.reshuffle();
    resetPot();
    m_CurrentPlayerIndex = 0;

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

    for (auto& player : m_Players) {
        if(player.hasHand())
            return;
        
        Card c1 = m_Deck.deal();
        Card c2 = m_Deck.deal();

        player.addCardToHand(c1);
        player.addCardToHand(c2);

        if (player.isHuman()) {
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
void GameLogic::addToPot(int amount) {
    std::vector<int> chipValues = {1000000, 500000, 100000, 50000, 10000};

    for (int chip : chipValues) {
        while (amount >= chip) {
            m_PotChips[chip]++;
            amount -= chip;
        }
    }

    std::cout << "[DEBUG] Added to pot: " << amount << "\n";
}

void GameLogic::collectBet(Player* player, int amount) {
    std::cout << "[DEBUG] Collecting bet of " << amount << "\n";
    // Logic for placing bets
}

void GameLogic::resetPot() {
    m_PotChips.clear();
}

/*
  ==============================================================================
    Turns
  ==============================================================================
*/
void GameLogic::handleDealing(Uint32 dt) {
    if (m_TimeLeft > dt) {
        m_TimeLeft -= dt;
    } else {
        m_TimeLeft = 0;
    }

    // // If the dealing is done
    // if (m_DealIndex >= m_DealSequence.size()) {
    //     setState(GameState::PlayerTurn);
    //     return;
    // }

    if (m_TimeLeft == 0) {
        dealCards();
        setState(GameState::PlayerTurn);
        return;
    }

}

void GameLogic::handlePlayerTurn(Uint32 deltaTime) {
    // Decrement the time left
    if (m_TimeLeft > deltaTime) {
        m_TimeLeft -= deltaTime;
    } else {
        m_TimeLeft = 0;
    }

    // If time runs out, force an action
    if (m_TimeLeft == 0) {
        std::cout << "[DEBUG] Player timed out, forcing fold\n";
        // Go to next state
        setState(GameState::AITurn);
        return;
    }
}

void GameLogic::handleAITurn(Uint32 dt) {
    if (m_TimeLeft > dt) {
        m_TimeLeft -= dt;
    } else {
        m_TimeLeft = 0;
    }

    if (m_TimeLeft == 0) {
        // do AI action
        std::cout << "[DEBUG] AI acts\n";
        setState(GameState::Showdown);
    }
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
        resetRound();
        setState(GameState::DealingCards);
    }
}

void GameLogic::onPlayerAction() {
    if (m_CurrentState == GameState::PlayerTurn) {
        
        

        setState(GameState::AITurn);
    }
}

void GameLogic::onAIAction() {
    if (m_CurrentState == GameState::AITurn) {
        
    }
}

GameState GameLogic::getState() const {
    return m_CurrentState;
}

void GameLogic::setState(GameState newState) {
    m_CurrentState = newState;
    switch (newState) {
        case GameState::DealingCards:
            m_TimeLeft = 2000;  // 2 seconds
            // maybe also shuffle deck or deal here
            std::cout << "[DEBUG] Dealing cards\n";
            break;
        case GameState::PlayerTurn:
            m_TimeLeft = 10000; // 10 seconds for player to act
            std::cout << "[DEBUG] It is my turn\n";
            break;
        case GameState::AITurn:
            m_TimeLeft = 3000;  // AI acts in up to 3 seconds
            std::cout << "[DEBUG] AI thinking\n";
            break;
        case GameState::Showdown:
            m_TimeLeft = 2000;  // show results for 2 seconds
            std::cout << "[DEBUG] Showdown\n";
            break;
    }
}