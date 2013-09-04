#ifndef COMPONENTDIALOG_H
#define COMPONENTDIALOG_H

#include <QDialog>
#include "datamodel.h"

namespace Ui {
class ComponentDialog;
}

class ComponentDialog : public QDialog
{
    Q_OBJECT
private:
    QString id,name,unit,des;
    double value;
    DataModel *dat;

public:
    explicit ComponentDialog(const QStringList &component, DataModel *_dat, QWidget *parent = 0);
    ~ComponentDialog();
    void checkAll();
    bool isModified;

private slots:
    void on_idCheck_stateChanged(int arg1);
    void on_checkBox_stateChanged(int arg1);
    void on_idEdit_textChanged(const QString &arg1);
    void on_nameEdit_textChanged(const QString &arg1);
    void on_valueEdit_textChanged(const QString &arg1);
    void on_unitEdit_textChanged(const QString &arg1);
    void on_desEdit_textChanged();
    void on_applyButton_clicked();
    void on_closeButton_clicked();

private:
    Ui::ComponentDialog *ui;
};

#endif // COMPONENTDIALOG_H
