#ifndef SERGEANT_H
#define SERGEANT_H

#include "agent.h"
#include "bfs.h"

class Sergeant : public Agent {
public:
    Sergeant(const QString& owner, MapCell* start);

    // اکشن‌ها
    QVector<MapCell*> possibleMoves() override; // Move
    void controlCell(MapCell* cell);           // Control
    void releaseCell(MapCell* cell);           // Release
    bool attackAgent(Agent* target);           // Attack

    int diceCount() const override { return 1; }

    int calculateAttackValue(const QVector<MapCell*>& path,
                             Agent* target) const override;
};

#endif
