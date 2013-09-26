#include "componentdialog.h"
#include "ui_componentdialog.h"
#include <QMessageBox>

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
    dat = _dat;

    ui->idEdit->setText(id);
    ui->nameEdit->setText(name);
    ui->valueEdit->setText(QString::number(value)); ui->valueEdit->setValidator(new QDoubleValidator());
    ui->unitEdit->setText(unit);
    ui->desEdit->setPlainText(des);

    isModified = false;
}

ComponentDialog::~ComponentDialog()
{
    delete ui;
}

void ComponentDialog::on_idCheck_stateChanged(int arg1)
{
    if(arg1==Qt::Checked) {
        ui->idEdit->setReadOnly(false);
    }
    else {
        ui->idEdit->setReadOnly(true);
        ui->idEdit->setText(id);
    }
    checkAll();
}

void ComponentDialog::on_checkBox_stateChanged(int arg1)
{
    if(arg1==Qt::Checked) {
        ui->nameEdit->setReadOnly(false);
        ui->valueEdit->setReadOnly(false);
        ui->unitEdit->setReadOnly(false);
        ui->desEdit->setReadOnly(false);
    }
    else {
        ui->nameEdit->setReadOnly(true);
        ui->nameEdit->setText(name);
        ui->valueEdit->setReadOnly(true);
        ui->valueEdit->setText(QString::number(value));
        ui->unitEdit->setReadOnly(true);
        ui->unitEdit->setText(unit);
        ui->desEdit->setReadOnly(true);
        ui->desEdit->setPlainText(des);
    }
    checkAll();
}

void ComponentDialog::checkAll() {
    if (ui->idEdit->text()==id &&
        ui->nameEdit->text()==name &&
        ui->valueEdit->text()==QString::number(value) &&
        ui->unitEdit->text()==unit &&
        ui->desEdit->toPlainText()==des)
        ui->applyButton->setEnabled(false);
    else
        ui->applyButton->setEnabled(true);
}

void ComponentDialog::on_idEdit_textChanged(const QString &arg1)
{
    checkAll();
}

void ComponentDialog::on_nameEdit_textChanged(const QString &arg1)
{
    checkAll();
}

void ComponentDialog::on_valueEdit_textChanged(const QString &arg1)
{
    checkAll();
}

void ComponentDialog::on_unitEdit_textChanged(const QString &arg1)
{
    checkAll();
}

void ComponentDialog::on_desEdit_textChanged()
{
    checkAll();
}

void ComponentDialog::on_applyButton_clicked()
{
    if(ui->idEdit->text()!=id) {
        if(dat->modifyComponent(id,tr("Id"),ui->idEdit->text())) {
            id = ui->idEdit->text();
            isModified = true;
        }
        else {
            ZtLog log;
            dat->logger.pop(log);
            QMessageBox::critical(this,this->windowTitle(),log.content);
            ui->idEdit->setText(id);
        }
    }
    if(ui->nameEdit->text()!=name) {
        if(dat->modifyComponent(id,tr("Name"),ui->nameEdit->text())) {
            name = ui->nameEdit->text();
            isModified = true;
        }
        else {
            ZtLog log;
            dat->logger.pop(log);
            QMessageBox::critical(this,this->windowTitle(),log.content);
            ui->nameEdit->setText(name);
        }
    }
    if(ui->valueEdit->text().toDouble()!=value) {
        if(dat->modifyComponent(id,tr("Value"),ui->valueEdit->text())) {
            value = ui->valueEdit->text().toDouble();
            ui->valueEdit->setText(QString::number(value));
            isModified = true;
        }
        else {
            ZtLog log;
            dat->logger.pop(log);
            QMessageBox::critical(this,this->windowTitle(),log.content);
            ui->valueEdit->setText(QString::number(value));
        }
    }
    if(ui->unitEdit->text()!=unit) {
        if(dat->modifyComponent(id,tr("Unit"),ui->unitEdit->text())) {
            unit = ui->unitEdit->text();
            isModified = true;
        }
        else {
            ZtLog log;
            dat->logger.pop(log);
            QMessageBox::critical(this,this->windowTitle(),log.content);
            ui->unitEdit->setText(unit);
        }
    }
    if(ui->desEdit->toPlainText()!=des) {
        if(dat->modifyComponent(id,tr("Description"),ui->desEdit->toPlainText())) {
            des = ui->desEdit->toPlainText();
            isModified = true;
        }
        else {
            ZtLog log;
            dat->logger.pop(log);
            QMessageBox::critical(this,this->windowTitle(),log.content);
            ui->desEdit->setPlainText(des);
        }
    }
    ui->applyButton->setEnabled(false);
}

void ComponentDialog::on_closeButton_clicked()
{
    checkAll();
    if(ui->applyButton->isEnabled()) {
        if(QMessageBox::question(this,this->windowTitle(),
                              tr("There are modifications, do you want to close without applying them?"))
                ==QMessageBox::No)
            return;
    }
    reject();
}
