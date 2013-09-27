#include "addfeaturedialog.h"
#include "ui_addfeaturedialog.h"
#include <QMessageBox>

AddFeatureDialog::AddFeatureDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddFeatureDialog)
{
    ui->setupUi(this);

    // parameters
    id = tr("F?"); ui->idEdit->setText(id);
    name = tr("Component"); ui->nameEdit->setText(name);
    unit = QString(); ui->unitEdit->setText(unit);
    des = QString(); ui->desEdit->setPlainText(des);
}

AddFeatureDialog::~AddFeatureDialog()
{
    delete ui;
}

void AddFeatureDialog::on_createButton_clicked()
{
    id = ui->idEdit->text();
    name = ui->nameEdit->text();
    unit = ui->unitEdit->text();
    des = ui->desEdit->toPlainText();

    if(id.isEmpty()) {
        QMessageBox::critical(this,this->windowTitle(),
                              tr("The id of the new feature can't be empty!"));
    }
    else if(name.isEmpty()) {
        QMessageBox::critical(this,this->windowTitle(),
                              tr("The name of the new feature can't be empty!"));
    }
    else
        accept();
}
