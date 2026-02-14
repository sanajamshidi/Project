#pragma once
#include <QVector>

class DiceResult {
public:
    QVector<int> values;
    int sum() const;
};

class Dice {
public:
    static DiceResult roll(int count); // همیشه D10
};
