#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include <QDialog>

namespace Ui {
class PlayerInfo;
}

class PlayerInfo : public QDialog
{
    Q_OBJECT

public:
    explicit PlayerInfo(QWidget *parent = nullptr);
    ~PlayerInfo();

private slots:

    void on_Next_clicked();


private:
    Ui::PlayerInfo *ui;
    bool CheckName ( const QString &name ) ;


};

#endif // PLAYERINFO_H
