#pragma once

#include <vector>
#include <memory>

#include "Deck.h"
#include "Player.h"
#include "AIPlayer.h"

enum class GameState {
    DealingCards,
    BettingRound,
    Showdown,
    LostGame
};

enum class ActionType {
    Fold,
    Check,
    Call,
    Bet,
    Raise,
    AllIn,
};

class GameLogic {
public:
    GameLogic();

    void update(Uint32 deltaTime);

/*
  ==============================================================================
    Betting system
  ==============================================================================
*/    
    void onPlayerAction(int playerIndex, ActionType action, int amount);
    void handleFold(int playerIndex);
    void handleCheck(int playerIndex);
    void handleCall(int playerIndex);
    void handleBet(int playerIndex, int betAmount);
    void handleRaise(int playerIndex, int raiseAmount);
    void handleAllIn(int playerIndex);
    void collectBetsToPot();
    //void addToPot(int amount);
    void collectBet(Player* player, int amount);
    void resetPot();
    void resetHighestBet();
    void startBettingRound();
    void endRound();
    void distributePotToWinner(int winnerIndex);
    void nextPlayerTurn();
    void checkBettingRoundEnd();
    bool isActionValid(int playerIndex, ActionType action, int amount);
    int countActivePlayers();


    void resetGame();
    void resetRound();
    void dealCards();
    
    int getPot() const;
    int getStartingPlayerIndex() const;
    int getCurrentTurnIndex() const;
    int getHighestBet() const;
    int getFirstToActIndex() const;
    int getLastAggressorIndex() const;
    int getBankroll(int playerIndex) const;
    GameState getState() const;
    Deck& getDeck();
    std::vector<Player>& getPlayers();

private:
    void setState(GameState newState);

    void startDealing();
    void handleDealing(Uint32 deltaTime);
    void handleBetting(Uint32 deltaTime);
    void handleShowdown(Uint32 deltaTime);
    void handleLostGame(Uint32 deltaTime);

    GameState m_CurrentState;
    Uint32 m_TimeLeft{0};

    Deck m_Deck;
    std::vector<Player> m_Players;
    //std::map<int, int> m_PotChips;

/*
  ==============================================================================
    Betting system
  ==============================================================================
*/
    int m_StartingPlayerIndex{0};
    int m_CurrentTurnIndex{0};
    int m_HighestBet{0};
    int m_Pot{0};
    std::vector<int> playerBets;
    std::vector<bool> m_HasCalled;

    int m_FirstToActIndex {0};
    int m_LastAggressorIndex{-1}; // who last bet or raised, -1 if nobody bet yet

    //std::vector<DealEvent> m_DealSequence;
    //int m_DealIndex{0};
};
