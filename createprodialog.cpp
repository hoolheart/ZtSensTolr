#include "createprodialog.h"
#include "ui_createprodialog.h"
#include <QMessageBox>
#include <QFileInfo>
#include <QFileDialog>

CreateProDialog::CreateProDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateProDialog)
{
    ui->setupUi(this);
    name = tr("project1");
    team = tr("team1");
    des = QString();
    filename = QString();
    ui->nameEdit->setText(name);
    ui->teamEdit->setText(team);
    ui->desEdit->setText(des);
    ui->pathEdit->setText(filename);
}

CreateProDialog::~CreateProDialog()
{
    delete ui;
}

void CreateProDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void CreateProDialog::on_chooseButton_clicked()
{
    QFileDialog tmp(this,tr("Select a store location..."));
    tmp.setFileMode(QFileDialog::AnyFile);
    tmp.setAcceptMode(QFileDialog::AcceptSave);
    tmp.setNameFilter(tr("Sensitivity & Tolerance Analysis project file (*.tol)"));
    QString ftype = ".tol";

    if(tmp.exec() == QDialog::Accepted) {
        QString fn = tmp.selectedFiles()[0];
        if(fn.right(ftype.length())!=ftype) fn += ftype;
        QFileInfo f(fn);
        ui->pathEdit->setText(f.absoluteFilePath());
    }
}

void CreateProDialog::on_createButton_clicked()
{
    name = ui->nameEdit->text();
    team = ui->teamEdit->text();
    des = ui->desEdit->toPlainText();
    filename = ui->pathEdit->text();

    if (name.isEmpty()) {
        QMessageBox::critical(this,this->windowTitle(),
                              tr("The name of the new project can't be empty!"));
    }
    else if (team.isEmpty()) {
        QMessageBox::critical(this,this->windowTitle(),
                              tr("The team of the new project can't be empty!"));
    }
    else if (filename.isEmpty()) {
        QMessageBox::critical(this,this->windowTitle(),
                              tr("The store location of the new project can't be empty!"));
    }
    else
        accept();
}
