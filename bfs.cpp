#include "bfs.h"
#include <QQueue>

QVector<MapCell*> bfs(MapCell* start, MapCell* end) {
    if (!start || !end) return {};

    QVector<MapCell*> visited;      // خانه‌های بازدید شده
    QVector<MapCell*> res;          // ترتیب بازدید واقعی
    QQueue<MapCell*> queue;         // صف FIFO

    queue.enqueue(start);           // خانه شروع وارد صف
    visited.append(start);

    while(!queue.isEmpty()) {
        MapCell* current = queue.dequeue();  // خانه اول خارج می‌شود
        res.append(current);                 // ذخیره ترتیب بازدید

        if(current == end) break;            // رسیدن به مقصد

        // همسایگان
        for(MapCell* neighbor : current->neighbors) {
            if(visited.contains(neighbor)) continue;
            // خانه‌ای که مهره دارد را نادیده بگیرید مگر اینکه مقصد باشد
            if(neighbor->occupant && neighbor != end) continue;

            queue.enqueue(neighbor);          // خانه جدید وارد صف می‌شود
            visited.append(neighbor);         // علامت بازدید
        }
    }

    return res;  // آرایه ترتیب بازدید خانه‌ها
}
