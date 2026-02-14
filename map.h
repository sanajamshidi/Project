#ifndef MAP_H
#define MAP_H

#include <QString>
#include <QVector>

// تعریف enum کنترل سلول
enum ControlStatus { Neutral, ControlledByA, ControlledByB };

// تعریف struct MapCell
struct MapCell {
    QString name;
    int level;                     // برای سطح سلول
    ControlStatus control;         // Neutral, ControlledByA, ControlledByB
    bool scoutedByA;               // همان scoutedByP1
    bool scoutedByB;               // همان scoutedByP2
    class Agent* occupant = nullptr; // اشاره‌گر به عامل روی این سلول
    QVector<MapCell*> neighbors;   // سلول‌های مجاور
};

// تعریف کلاس Map
class Map {
public:
    bool loadMap(const QString &path);
    MapCell* findCellByName(const QString& name);
    bool loadPhase2(const QString &path);
    void setNeighbors();

private:
    QVector<MapCell> cells;
    QVector<QVector<MapCell>> mapCells;
};

#endif // MAP_H
