#include "featuredialog.h"
#include "ui_featuredialog.h"
#include <QMessageBox>

FeatureDialog::FeatureDialog(const QStringList &feature, DataModel *_dat, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FeatureDialog)
{
    ui->setupUi(this);

    id = feature[0];
    name = feature[1];
    unit = feature[2];
    des = feature[3];
    dat = _dat;

    ui->idEdit->setText(id);
    ui->nameEdit->setText(name);
    ui->unitEdit->setText(unit);
    ui->desEdit->setPlainText(des);

    connect(ui->idEdit,SIGNAL(textChanged(QString)),this,SLOT(checkAll()));
    connect(ui->nameEdit,SIGNAL(textChanged(QString)),this,SLOT(checkAll()));
    connect(ui->unitEdit,SIGNAL(textChanged(QString)),this,SLOT(checkAll()));
    connect(ui->desEdit,SIGNAL(textChanged(QString)),this,SLOT(checkAll()));

    isModified = false;
}

FeatureDialog::~FeatureDialog()
{
    delete ui;
}

void FeatureDialog::checkAll() {
    if (ui->idEdit->text()==id &&
        ui->nameEdit->text()==name &&
        ui->unitEdit->text()==unit &&
        ui->desEdit->toPlainText()==des)
        ui->applyButton->setEnabled(false);
    else
        ui->applyButton->setEnabled(true);
}

void FeatureDialog::on_idCheck_stateChanged(int arg1)
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

void FeatureDialog::on_checkBox_stateChanged(int arg1)
{
    if(arg1==Qt::Checked) {
        ui->nameEdit->setReadOnly(false);
        ui->unitEdit->setReadOnly(false);
        ui->desEdit->setReadOnly(false);
    }
    else {
        ui->nameEdit->setReadOnly(true);
        ui->nameEdit->setText(name);
        ui->unitEdit->setReadOnly(true);
        ui->unitEdit->setText(unit);
        ui->desEdit->setReadOnly(true);
        ui->desEdit->setPlainText(des);
    }
    checkAll();
}

void FeatureDialog::on_applyButton_clicked()
{
    if(ui->idEdit->text()!=id) {
        if(dat->modifyFeature(id,tr("Id"),ui->idEdit->text())) {
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
        if(dat->modifyFeature(id,tr("Name"),ui->nameEdit->text())) {
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
    if(ui->unitEdit->text()!=unit) {
        if(dat->modifyFeature(id,tr("Unit"),ui->unitEdit->text())) {
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
        if(dat->modifyFeature(id,tr("Description"),ui->desEdit->toPlainText())) {
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

void FeatureDialog::on_closeButton_clicked()
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
