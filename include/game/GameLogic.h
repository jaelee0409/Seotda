#pragma once

#include <vector>
#include <memory>

#include "Deck.h"
#include "Player.h"
#include "AIPlayer.h"

enum class GameState {
    DealingCards,
    PlayerTurn,
    AITurn,
    Showdown,
};

struct DealEvent {
    int playerIndex;
    Card& card;
    bool finished;
};

class GameLogic {
public:
    GameLogic();

    void update(Uint32 deltaTime);
    void onPlayerAction();
    void onAIAction();

    void resetGame();
    void resetRound();
    void dealCards();
    void addToPot(int amount);
    void collectBet(Player* player, int amount);
    void resetPot();

    GameState getState() const;
    Deck& getDeck() { return m_Deck; }
    std::vector<Player>& getPlayers() { return m_Players; }

private:
    void setState(GameState newState);

    void startDealing();
    void handleDealing(Uint32 deltaTime);

    void handlePlayerTurn(Uint32 deltaTime);
    void handleAITurn(Uint32 deltaTime);
    void handleShowdown(Uint32 deltaTime);

    GameState m_CurrentState;
    Uint32 m_TimeLeft{0};

    Deck m_Deck;
    std::vector<Player> m_Players;
    std::map<int, int> m_PotChips;

/*
  ==============================================================================
    Betting system
  ==============================================================================
*/
    int m_CurrentPlayerIndex; // Track the current player’s turn
    int m_HighestBet;
    std::vector<int> playerBets;
    std::vector<bool> m_HasCalled;

    std::vector<DealEvent> m_DealSequence;
    int m_DealIndex{0};
};
