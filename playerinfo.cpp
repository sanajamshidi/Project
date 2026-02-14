#include "playerinfo.h"
#include "ui_playerinfo.h"
#include <qmessagebox.h>
#include "selectmap.h"
#include "gameboard.h"
#include <QFile>



bool PlayerInfo :: CheckName ( const QString &name ) {
    if (name.length() < 8)
        return false;

    if (!name[0].isLetter())
        return false;

    bool hasDigit = false;
    bool hasUpper = false;
    bool hasLower = false;
    bool hasSpecial = false;

    QString specials = "!@#$%^&*()_+-=[]{}|;:'\",.<>/?";

    for (QChar c : name)
    {
        if (c.isDigit()) hasDigit = true;
        if (c.isUpper()) hasUpper = true;
        if (c.isLower()) hasLower = true;
        if (specials.contains(c)) hasSpecial = true;
    }

    return hasDigit && hasUpper && hasLower && hasSpecial;
}

PlayerInfo::PlayerInfo(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PlayerInfo)
{
    ui->setupUi(this);
    this->showFullScreen();
}
PlayerInfo::~PlayerInfo()
{
    delete ui;
}

void PlayerInfo::on_Next_clicked()
{
    QString name1 = ui->player1->text();
    QString name2 = ui->player2->text();

    if (name1.isEmpty() || name2.isEmpty()) {
        QMessageBox::warning(this, "Error", "please eneter names of both players.");
        return;
    }

    if (!CheckName(name1)) {
        QMessageBox::warning(this, "Error", "The first player name is not valid!");
        return;
    }

    if (!CheckName(name2)) {
        QMessageBox::warning(this, "Error", "The second player name is not valid!");
        return;
    }



    SelectMap mapDialog(this);
    if (mapDialog.exec() == QDialog::Accepted) {

        QString pathPhase1 = mapDialog.selectedMapPath();        // فایل Phase1
        QString pathPhase2 = mapDialog.selectedPhase2Path();    // فایل Phase2 متناظر

        GameBoard *gb = new GameBoard();

        gb->setPlayerNames(name1, name2);


        gb->loadMap(pathPhase1, pathPhase2);
        gb->updateBoardView();
    }
}

