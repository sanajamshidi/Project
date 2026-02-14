#include "map.h"
#include "scout.h"
#include "sniper.h"
#include "sergeant.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

bool Map::loadMap(const QString &path){
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Cannot open file:" << path;
        return false;
    }

    mapCells.clear();
    QTextStream in(&file);
    while(!in.atEnd()){
        QString line = in.readLine().trimmed();
        if(line.isEmpty()) continue;

        QStringList parts = line.split('|', Qt::SkipEmptyParts);
        QVector<MapCell> row;
        for(QString p : parts){
            QStringList sub = p.split(':');
            if(sub.size()!=2) continue;

            MapCell cell;
            cell.name = sub[0].trimmed();
            cell.level = sub[1].trimmed().toInt();
            row.append(cell);
        }
        mapCells.append(row);
    }

    file.close();
    return true;
}

MapCell* Map::findCellByName(const QString& name){
    for(auto &row : mapCells){
        for(auto &cell : row){
            if(cell.name==name) return &cell;
        }
    }
    return nullptr;
}

bool Map::loadPhase2(const QString &path){
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Cannot open phase2 file:" << path;
        return false;
    }

    QTextStream in(&file);
    while(!in.atEnd()){
        QString line = in.readLine().trimmed();
        if(line.isEmpty()) continue;

        QStringList parts = line.split(',');
        if(parts.size()!=2) continue;

        QString left = parts[0].trimmed();   // مثل A01:A
        QString status = parts[1].trimmed(); // Mark, Control, Scout, Sniper, Sergeant

        QString cellName = left.section(':',0,0);
        QString player = left.section(':',1,1);

        MapCell* cell = findCellByName(cellName);
        if(!cell) continue;

        if(status=="Mark"){
            if(player == "A") cell->scoutedByA = true;
            else cell->scoutedByB = true;
        } else if(status=="Control"){
            if(player == "A") cell->control = ControlledByA;
            else cell->control = ControlledByB;
        } else {
            // Agent
            Agent* agent = nullptr;
            if(status=="Scout") agent = new Scout(player, cell);
            else if(status=="Sniper") agent = new Sniper(player, cell);
            else if(status=="Sergeant") agent = new Sergeant(player, cell);

            cell->occupant = agent;
        }
    }

    file.close();
    return true;
}

void Map::setNeighbors(){
    int rows = mapCells.size();
    for(int r=0; r<rows; r++){
        int cols = mapCells[r].size();
        for(int c=0; c<cols; c++){
            MapCell* cell = &mapCells[r][c];

            // چپ و راست
            if(c>0) cell->neighbors.append(&mapCells[r][c-1]);
            if(c<cols-1) cell->neighbors.append(&mapCells[r][c+1]);

            // بالا
            if(r>0){
                int upperCols = mapCells[r-1].size();
                int leftUpper = c;
                int rightUpper = c+1;

                if(leftUpper < upperCols) cell->neighbors.append(&mapCells[r-1][leftUpper]);
                if(rightUpper < upperCols) cell->neighbors.append(&mapCells[r-1][rightUpper]);
            }

            // پایین
            if(r<rows-1){
                int lowerCols = mapCells[r+1].size();
                int leftLower = c;
                int rightLower = c+1;

                if(leftLower < lowerCols) cell->neighbors.append(&mapCells[r+1][leftLower]);
                if(rightLower < lowerCols) cell->neighbors.append(&mapCells[r+1][rightLower]);
            }
        }
    }
}
