#include "gameboard.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QPixmap>
#include <QMessageBox>



void GameBoard::setPlayerNames(const QString& a,
                               const QString& b)
{
    playerAName = a;
    playerBName = b;
}

GameBoard::GameBoard(QWidget *parent)
    : QDialog(parent)

{


    this->showFullScreen();

    boardWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(boardWidget);
    boardWidget->setStyleSheet("background-color: #8FBC8F;");
}

GameBoard::~GameBoard()
{
}


void GameBoard::gameOver(const QString& winner) {
    QString winnerName;
    if(winner == "A") winnerName = playerAName;
    else if(winner == "B") winnerName = playerBName;
    else winnerName = "Unknown";

    qDebug() << "Game Over! Winner:" << winnerName;

    QMessageBox::information(this, "Game Over", "Winner: " + winnerName);

    this->close();  // یا reset بازی
}



void GameBoard::updateBoardView() {
    // اینجا کد رسم نقشه روی UI میره
    for(int r = 0; r < mapCells.size(); ++r) {
        for(int c = 0; c < mapCells[r].size(); ++c) {

        }
    }
}


QString GameBoard::getImageForLevel(int level){
    switch (level) {
    case 0: return ":/card/image0.JPG";
    case 1: return ":/card/image1.JPG";
    case 2: return ":/card/image2.JPG";
    default: return ":/card/image0.JPG";
    }
}

void GameBoard::loadMap(const QString &phase1Path, const QString &phase2Path)
{
    Q_UNUSED(phase2Path);

    const int tileW = 70;
    const int tileH = 70;

    mapCells.clear();

    QFile file(phase1Path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Cannot open file!";
        return;
    }

    QTextStream in(&file);

    while(!in.atEnd())
    {
        QString line = in.readLine().trimmed();
        if(line.isEmpty())
            continue;

        QStringList rawCells = line.split("|", Qt::SkipEmptyParts);

        QVector<MapCell> row;

        for(const QString &cellTextRaw : rawCells)
        {
            QString cellText = cellTextRaw.trimmed();
            if(cellText.isEmpty())
                continue;

            // A01:0
            QStringList parts = cellText.split(":");
            if(parts.size() != 2)
                continue;

            MapCell cell;
            cell.name = parts[0].trimmed();        // A01
            cell.level = parts[1].trimmed().toInt(); // 0

            row.append(cell);
        }

        if(!row.isEmpty())
            mapCells.append(row);
    }

    file.close();

    if(mapCells.isEmpty()){
        qDebug() << "Map is empty!";
        return;
    }

    // ---------- رسم ----------

    QList<QWidget*> children = boardWidget->findChildren<QWidget*>();
    qDeleteAll(children);

    int rows = mapCells.size();
    int cols = mapCells[0].size();

    int boardWidth = cols * tileW + tileW/2;
    int boardHeight = rows * tileH;

    int startX = (1300 - boardWidth) / 2;
    int startY = (700 - boardHeight) / 2;

    for(int r = 0; r < rows; ++r){
        for(int c = 0; c < mapCells[r].size(); ++c){

            QWidget *cellWidget = new QWidget(boardWidget);

            int offset = (r % 2 == 1) ? tileW / 2 : 0;

            cellWidget->setGeometry(
                startX + c * tileW + offset,
                startY + r * tileH,
                tileW,
                tileH
                );

            cellWidget->setStyleSheet("background:#ffffff; border:1px solid #444;");

            QLabel *imgLabel = new QLabel(cellWidget);
            imgLabel->setPixmap(
                QPixmap(getImageForLevel(mapCells[r][c].level))
                    .scaled(tileW, tileH*0.75, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation)
                );
            imgLabel->setGeometry(0,0,tileW,tileH*0.75);
            imgLabel->setAlignment(Qt::AlignCenter);

            QLabel *txtLabel = new QLabel(mapCells[r][c].name, cellWidget);
            txtLabel->setGeometry(0,tileH*0.75,tileW,tileH*0.25);
            txtLabel->setAlignment(Qt::AlignCenter);
            txtLabel->setStyleSheet("color:black; font-weight:bold;");
        }
    }

    boardWidget->show();

    qDebug() << "Map Loaded. Rows:" << rows;
}
