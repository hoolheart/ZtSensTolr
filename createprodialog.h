#ifndef CREATEPRODIALOG_H
#define CREATEPRODIALOG_H

#include <QDialog>

namespace Ui {
class CreateProDialog;
}

class CreateProDialog : public QDialog
{
    Q_OBJECT
public:
    QString name;
    QString team;
    QString des;
    QString filename;
    
public:
    explicit CreateProDialog(QWidget *parent = 0);
    ~CreateProDialog();

protected:
    void changeEvent(QEvent *e);
    
private slots:
    void on_chooseButton_clicked();
    void on_createButton_clicked();

private:
    Ui::CreateProDialog *ui;
};

#endif // CREATEPRODIALOG_H
