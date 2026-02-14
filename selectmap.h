#ifndef SELECTMAP_H
#define SELECTMAP_H

#include <QDialog>
#include <QString>

namespace Ui {
class SelectMap;
}

class SelectMap : public QDialog
{
    Q_OBJECT

public:
    explicit SelectMap(QWidget *parent = nullptr);
    ~SelectMap();

    QString selectedMapPath() const;       // مسیر فایل Phase1
    QString selectedPhase2Path() const;    // مسیر فایل Phase2 متناظر

private slots:
    void mapSelectionChanged(const QString &path);
    void on_okButton_clicked();

private:
    Ui::SelectMap *ui;
    QString chosenMap;
};

#endif // SELECTMAP_H
