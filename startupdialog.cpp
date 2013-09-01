#include "startupdialog.h"
#include "ui_startupdialog.h"

StartupDialog::StartupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartupDialog)
{
    p = (MainWindow *)parent;
    ui->setupUi(this);
}

StartupDialog::~StartupDialog()
{
    delete ui;
}

void StartupDialog::on_createButton_clicked()
{
    if(p->createFile())
        accept();
}

void StartupDialog::on_openButton_clicked()
{
    if(p->openFile())
        accept();
}
