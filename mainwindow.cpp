#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "playerinfo.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label1->lower();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Play_clicked()
{
    hide();
    PlayerInfo dlg(this) ;
    dlg.exec() ;
}

