#ifndef BFS_H
#define BFS_H

#include <QVector>
#include "map.h"

// BFS: مسیر بین start و end
// - queue: صف FIFO
// - visited: خانه‌های بازدید شده
// - res: ترتیب بازدید خانه‌ها
QVector<MapCell*> bfs(MapCell* start, MapCell* end);

#endif // BFS_H
