#include "mapcell.h"

MapCell::MapCell() : name(""), level(0) {}
MapCell::MapCell(const QString& name, int level) : name(name), level(level) {}
QString MapCell::getName() const { return name; }
int MapCell::getLevel() const { return level; }
