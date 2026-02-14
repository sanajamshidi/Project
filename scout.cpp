#include "scout.h"
#include <QRandomGenerator>

Scout::Scout(const QString& owner, MapCell* start)
    : Agent(owner, start)
{
    hp = 5;
    if(position) scoutCell(position); // دیده‌بانی خانه شروع
}

// Move
QVector<MapCell*> Scout::possibleMoves() {
    return position->neighbors;
}

// Scout / دیده‌بانی
void Scout::scoutCell(MapCell* cell) {
    if(owner == "A") cell->scoutedByA = true;
    else cell->scoutedByB = true;
}

// محاسبه معیار حمله
int Scout::calculateAttackValue(const QVector<MapCell*>& path, Agent* target) const {
    int sum = target->getHp();
    for(MapCell* c : path)
        sum += c->level;
    return sum;
}

// حمله
bool Scout::attackAgent(Agent* target) {
    QVector<MapCell*> path = bfs(position, target->getPosition());
    if(path.isEmpty()) return false;

    int attackValue = calculateAttackValue(path, target);
    bool success = false;

    for(int i = 0; i < diceCount(); ++i){
        int roll = QRandomGenerator::global()->bounded(1, 11); // 1 تا 10
        if(roll >= attackValue) success = true;
    }

    return success;
}
