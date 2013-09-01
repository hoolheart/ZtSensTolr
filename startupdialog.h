#ifndef STARTUPDIALOG_H
#define STARTUPDIALOG_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class StartupDialog;
}

class StartupDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit StartupDialog(QWidget *parent = 0);
    ~StartupDialog();
    
private slots:
    void on_createButton_clicked();
    void on_openButton_clicked();

private:
    Ui::StartupDialog *ui;
    MainWindow *p;
};

#endif // STARTUPDIALOG_H
