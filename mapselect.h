#ifndef MAPSELECT_H
#define MAPSELECT_H

#include <QDialog>

namespace Ui {
class MapSelect;
}

class MapSelect : public QDialog
{
    Q_OBJECT

public:
    explicit MapSelect(QWidget *parent = nullptr);
    ~MapSelect();

private:
    Ui::MapSelect *ui;
};

#endif // MAPSELECT_H
