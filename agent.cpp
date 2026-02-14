#include "agent.h"
#include "bfs.h"
#include <QRandomGenerator>

Agent::Agent(const QString& owner, MapCell* start)
    : owner(owner), position(start)
{
    if(position)
        position->occupant = this;
}

Agent::~Agent() {}

QString Agent::getOwner() const { return owner; }
int Agent::getHp() const { return hp; }
MapCell* Agent::getPosition() const { return position; }

bool Agent::moveTo(MapCell* dest)
{
    if(!dest) return false;
    if(dest->occupant) return false;
    if(!position->neighbors.contains(dest)) return false;

    position->occupant = nullptr;
    dest->occupant = this;
    position = dest;

    onMove();  // اگر Scout باشد mark انجام می‌دهد
    return true;
}

int Agent::calculateAttackValue(const QVector<MapCell*>& path,
                                Agent* target) const
{
    int sum = target->getHp();

    // حذف خانه مبدا از محاسبه
    for(int i = 1; i < path.size(); ++i)
        sum += path[i]->level;

    return sum;
}

bool Agent::attackAgent(Agent* target)
{
    if(!target) return false;

    // جلوگیری از حمله به هم‌تیمی
    if(target->getOwner() == owner)
        return false;

    QVector<MapCell*> path = bfs(position, target->getPosition());
    if(path.isEmpty()) return false;

    int attackValue = calculateAttackValue(path, target);

    DiceResult dice = Dice::roll(diceCount());

    for(int roll : dice.values) {
        if(roll >= attackValue)
            return true;
    }

    return false;
}
