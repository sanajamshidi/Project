#ifndef SNIPER_H
#define SNIPER_H

#include "agent.h"
#include "bfs.h"

class Sniper : public Agent {
public:
    Sniper(const QString& owner, MapCell* start);

    // اکشن‌ها
    QVector<MapCell*> possibleMoves() override; // Move
    bool attackAgent(Agent* target);           // Attack


    int calculateAttackValue(const QVector<MapCell*>& path,  Agent* target) const override;

    int diceCount() const override { return 3; }
};

#endif
