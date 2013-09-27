#ifndef ADDFEATUREDIALOG_H
#define ADDFEATUREDIALOG_H

#include <QDialog>

namespace Ui {
class AddFeatureDialog;
}

class AddFeatureDialog : public QDialog
{
    Q_OBJECT
public:
    QString id;
    QString name;
    QString unit;
    QString des;
    
public:
    explicit AddFeatureDialog(QWidget *parent = 0);
    ~AddFeatureDialog();
    
private slots:
    void on_createButton_clicked();

private:
    Ui::AddFeatureDialog *ui;
};

#endif // ADDFEATUREDIALOG_H
