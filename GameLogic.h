#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "deck.h"
#include "map.h"
#include "scout.h"
#include "sniper.h"
#include "sergeant.h"
#include <QVector>

class GameLogic {
public:
    Map gameMap;
    Deck deckA;
    Deck deckB;

    QString currentPlayer;  // "A" یا "B"
    Agent* currentAgent;    // ایجنت فعال در نوبت

    GameLogic() {
        currentPlayer = "A";
        currentAgent = nullptr;
    }

    void initialize() {
        deckA.initialize("A");
        deckB.initialize("B");
        deckA.shuffle();
        deckB.shuffle();
        currentPlayer = "A";
    }

    Card drawCurrentPlayerCard() {
        if(currentPlayer == "A") return deckA.drawCard();
        else return deckB.drawCard();
    }

    Agent* createAgentFromCard(const Card& card, MapCell* cell) {
        if(card.type == AgentType::Scout) return new Scout(currentPlayer, cell);
        if(card.type == AgentType::Sniper) return new Sniper(currentPlayer, cell);
        if(card.type == AgentType::Sergeant) return new Sergeant(currentPlayer, cell);
        return nullptr;
    }

    void switchTurn() {
        currentPlayer = (currentPlayer=="A") ? "B" : "A";
        currentAgent = nullptr;
    }

    bool checkGameOver() {
        // وقتی یکی از بازیکن‌ها کارت و ایجنت ندارد
        bool aHasAgents = playerHasAgents("A");
        bool bHasAgents = playerHasAgents("B");
        return !(aHasAgents && bHasAgents);
    }

    bool playerHasAgents(const QString& player) {
        for(auto& row : gameMap.mapCells){
            for(auto& cell : row){
                if(cell.occupant && cell.occupant->getOwner() == player)
                    return true;
            }
        }
        return false;
    }


    void GameLogic::removeOpponentCard(const Card& card)
    {
        if(currentPlayer == "A")
            deckB.removeFromGame(card);
        else
            deckA.removeFromGame(card);
    }

};

#endif
