#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QTreeWidget>
#include <QTabWidget>
#include <QCloseEvent>
#include "datamodel.h"
#include "tableview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    DataModel dat;

    // Widgets
    QTreeWidget * proTree;
    QTabWidget * tabs;
    QSplitter * central;
    TableView * comView, * feaView, * orthView;
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool createFile();
    bool openFile();
    void refresh();
    bool startup();
    
private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSaveAs_triggered();
    void on_actionSave_copy_as_triggered();
    void on_actionQuit_triggered();

private:
    Ui::MainWindow *ui;

protected:
    virtual void closeEvent ( QCloseEvent * event );
};

#endif // MAINWINDOW_H
