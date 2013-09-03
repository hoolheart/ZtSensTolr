#include "componentdialog.h"
#include "ui_componentdialog.h"

ComponentDialog::ComponentDialog(const QStringList &component, DataModel *_dat, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComponentDialog)
{
    ui->setupUi(this);

    id = component[0];
    name = component[1];
    value = component[2].toDouble();
    unit = component[3];
    des = component[4];

    ui->idEdit->setText(id);
    ui->nameEdit->setText(name);
    ui->valueEdit->setText(QString::number(value)); ui->valueEdit->setValidator(new QDoubleValidator());
    ui->unitEdit->setText(unit);
    ui->desEdit->setPlainText(des);
}

ComponentDialog::~ComponentDialog()
{
    delete ui;
}
