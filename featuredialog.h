#ifndef FEATUREDIALOG_H
#define FEATUREDIALOG_H

#include <QDialog>
#include "datamodel.h"

namespace Ui {
class FeatureDialog;
}

class FeatureDialog : public QDialog
{
    Q_OBJECT
private:
    QString id,name,unit,des;
    DataModel *dat;

public:
    explicit FeatureDialog(const QStringList &feature, DataModel *_dat, QWidget *parent = 0);
    ~FeatureDialog();
    bool isModified;

private slots:
    void checkAll();
    void on_idCheck_stateChanged(int arg1);
    void on_checkBox_stateChanged(int arg1);
    void on_applyButton_clicked();
    void on_closeButton_clicked();

private:
    Ui::FeatureDialog *ui;
};

#endif // FEATUREDIALOG_H
