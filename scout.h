#ifndef SCOUT_H
#define SCOUT_H

#include "agent.h"
#include "bfs.h"

class Scout : public Agent {
public:
    Scout(const QString& owner, MapCell* start);

    QVector<MapCell*> possibleMoves() override;  // Move
    void scoutCell(MapCell* cell);               // دیده‌بانی
    bool attackAgent(Agent* target);             // حمله

    int diceCount() const override { return 1; }

    int calculateAttackValue(const QVector<MapCell*>& path, Agent* target) const override;
};

#endif
