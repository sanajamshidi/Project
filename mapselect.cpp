#include "mapselect.h"
#include "ui_mapselect.h"

SelectMap::SelectMap(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SelectMap)
{
    ui->setupUi(this);
}

SelectMap::~SelectMap()
{
    delete ui;
}
