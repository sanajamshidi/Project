#ifndef AGENT_H
#define AGENT_H

#include <QString>
#include <QVector>
#include "map.h"
#include "dice.h"

enum class AgentType { Scout, Sniper, Sergeant };

class Agent {

protected:
    QString owner;     // "A" یا "B"
    int hp;
    MapCell* position;

   virtual int calculateAttackValue(const QVector<MapCell*>& path, Agent* target) const = 0;

public:
    Agent(const QString& owner, MapCell* start);
    virtual ~Agent();

    virtual int diceCount() const = 0;

    QString getOwner() const;
    int getHp() const;
    MapCell* getPosition() const;

    bool moveTo(MapCell* dest);

    bool attackAgent(Agent* target);

    virtual QVector<MapCell*> possibleMoves() = 0;

    virtual void onMove() {}   // برای Scout استفاده می‌شود
};

#endif // AGENT_H
