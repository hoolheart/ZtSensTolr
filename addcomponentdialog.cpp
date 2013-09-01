#include "addcomponentdialog.h"
#include "ui_addcomponentdialog.h"
#include <QDoubleValidator>
#include <QMessageBox>

AddComponentDialog::AddComponentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddComponentDialog)
{
    ui->setupUi(this);

    // parameters
    id = tr("C?"); ui->idEdit->setText(id);
    name = tr("Component"); ui->nameEdit->setText(name);
    value = 0; ui->valueEdit->setText(QString::number(value));
    ui->valueEdit->setValidator(new QDoubleValidator());
    unit = QString(); ui->unitEdit->setText(unit);
    des = QString(); ui->desEdit->setPlainText(des);
}

AddComponentDialog::~AddComponentDialog()
{
    delete ui;
}

void AddComponentDialog::on_createButton_clicked()
{
    id = ui->idEdit->text();
    name = ui->nameEdit->text();
    value = ui->valueEdit->text().toDouble();
    unit = ui->unitEdit->text();
    des = ui->desEdit->toPlainText();

    if(id.isEmpty()) {
        QMessageBox::critical(this,this->windowTitle(),
                              tr("The id of the new component can't be empty!"));
    }
    else if(name.isEmpty()) {
        QMessageBox::critical(this,this->windowTitle(),
                              tr("The name of the new component can't be empty!"));
    }
    else
        accept();
}
