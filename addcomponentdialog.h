#ifndef ADDCOMPONENTDIALOG_H
#define ADDCOMPONENTDIALOG_H

#include <QDialog>

namespace Ui {
class AddComponentDialog;
}

class AddComponentDialog : public QDialog
{
    Q_OBJECT
public:
    QString id;
    QString name;
    double value;
    QString unit;
    QString des;

public:
    explicit AddComponentDialog(QWidget *parent = 0);
    ~AddComponentDialog();

private slots:
    void on_createButton_clicked();

private:
    Ui::AddComponentDialog *ui;
};

#endif // ADDCOMPONENTDIALOG_H
