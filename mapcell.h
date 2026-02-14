#ifndef MAPCELL_H
#define MAPCELL_H

#pragma once
#include <QString>
#include <QPushButton>
#include <QList>

struct MapCell {
    QString id;
    int level = 0;

    QString owner; // "A" یا "B"
    bool markedByA = false;
    bool markedByB = false;
    bool controlledByA = false;
    bool controlledByB = false;

    QString pieceType; // "Sniper", "Scout", "Seargeant", ""

    QList<MapCell*> neighbors;
    QPushButton* widget = nullptr;
};

#endif // MAPCELL_H
