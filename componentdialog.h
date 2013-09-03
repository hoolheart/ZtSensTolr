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

private:
    Ui::ComponentDialog *ui;
};

#endif // COMPONENTDIALOG_H
