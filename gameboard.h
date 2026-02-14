#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QDialog>
#include <QVector>
#include <QLabel>
#include <QGridLayout>
#include <QWidget>

#include "agent.h"
#include "map.h"

class GameBoard : public QDialog
{
    Q_OBJECT

public:
    explicit GameBoard(QWidget *parent = nullptr);
    ~GameBoard();

    void setPlayerNames(const QString& a, const QString& b);
    void loadMap(const QString &phase1Path, const QString &phase2Path);
    void updateBoardView();

private:
    QString playerAName;
    QString playerBName;

    QWidget *boardWidget;
    QGridLayout *gridLayout;
    Map* gameMap;
    QVector<QVector<MapCell>> mapCells;

    QString getImageForLevel(int level);

    const int tileW = 80;
    const int tileH = 80;

    void handleSuccessfulAttack(Agent* attacker, Agent* target);
    void checkGameOver();
    int countControlledCells(const QString& player) const;
    bool playerHasAgents(const QString& player) const;
    void gameOver(const QString& winner);
};

#endif // GAMEBOARD_H
