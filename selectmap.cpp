#include "selectmap.h"
#include "ui_selectmap.h"
#include <QDebug>
#include <QFile>

SelectMap::SelectMap(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectMap)
{
    ui->setupUi(this);
    ui->okButton->setEnabled(false);

    // فایل اول را پیش‌فرض انتخاب کن
    ui->radioButton1->setChecked(true);
    mapSelectionChanged(":/map/1.txt");

    // اتصال RadioButtonها به تغییر نقشه
    connect(ui->radioButton1, &QRadioButton::toggled, this,
            [this](bool checked){ if(checked) mapSelectionChanged(":/map/1.txt"); });
    connect(ui->radioButton2, &QRadioButton::toggled, this,
            [this](bool checked){ if(checked) mapSelectionChanged(":/map/2.txt"); });
    connect(ui->radioButton3, &QRadioButton::toggled, this,
            [this](bool checked){ if(checked) mapSelectionChanged(":/map/3.txt"); });
    connect(ui->radioButton4, &QRadioButton::toggled, this,
            [this](bool checked){ if(checked) mapSelectionChanged(":/map/4.txt"); });
    connect(ui->radioButton5, &QRadioButton::toggled, this,
            [this](bool checked){ if(checked) mapSelectionChanged(":/map/5.txt"); });
}

SelectMap::~SelectMap()
{
    delete ui;
}

// مسیر فایل Phase1
QString SelectMap::selectedMapPath() const {
    return chosenMap;
}

// مسیر فایل Phase2 متناظر
QString SelectMap::selectedPhase2Path() const {
    QString path2 = chosenMap;
    if(path2.endsWith(".txt"))
        path2.replace(".txt", "_Phase2.txt"); // 1.txt -> 1_phase2.txt
    return path2;
}

// تغییر نقشه انتخابی
void SelectMap::mapSelectionChanged(const QString &path)
{
    QFile file(path);
    if(!file.exists()){
        qDebug() << "Map file not found:" << path;
        ui->okButton->setEnabled(false);
        return;
    }
    chosenMap = path;
    ui->okButton->setEnabled(true);
}

// دکمه OK
void SelectMap::on_okButton_clicked()
{
    accept();
}
