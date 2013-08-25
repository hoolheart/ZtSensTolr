#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include "createprodialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    proTree = new QTreeWidget();
    tabs = new QTabWidget(this);
    tabs->setTabsClosable(false);
    central = new QSplitter(Qt::Horizontal,this);
    central->addWidget(proTree);
    central->addWidget(tabs);
    setCentralWidget(central);

    dat.loadData(QString("E:\\Design\\GitHut\\ZtSensTolr\\dat_test1.tol"));
    dat.updateAll();
    comView = new TableView(&dat.components,this);
    feaView = new TableView(&dat.features,this);
    orthView = new TableView(&dat.orthogonalTable,this);

    tabs->addTab((QWidget *)comView,tr("Components"));
    tabs->addTab((QWidget *)feaView,tr("Features"));
    tabs->addTab((QWidget *)orthView,tr("Orthogonal Table"));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete proTree;
    delete comView; delete feaView; delete orthView;
    delete tabs;
    delete central;
}

bool MainWindow::createFile() {
    CreateProDialog tmp;
    if (tmp.exec()==QDialog::Accepted) {
        dat.createData(tmp.name,tmp.team,tmp.des,tmp.filename);
        return true;
    }
    else
        return false;
}

bool MainWindow::openFile() {
    QFileDialog openDiag(this,tr("Open a Sensitivity & Tolerance Analysis project file"));
    openDiag.setFileMode(QFileDialog::ExistingFile);
    openDiag.setAcceptMode(QFileDialog::AcceptOpen);
    openDiag.setNameFilter(tr("Sensitivity & Tolerance Analysis project file (*.tol)"));

    if(openDiag.exec() == QDialog::Accepted) {
        if(dat.loadData(openDiag.selectedFiles()[0]))
            return true;
        else {
            ZtLog log;
            dat.logger.pop(log);
            QMessageBox::critical(this,this->windowTitle(),log.content);
        }
    }
    return false;
}

void MainWindow::refresh() {
    dat.updateAll();
    comView->refresh();
    feaView->refresh();
    orthView->refresh();
}

void MainWindow::on_actionQuit_triggered()
{
    close();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (!dat.IsModified()) {
        event->accept();
        return;
    }

    QMessageBox tmp(QMessageBox::Question,tr("Sensitivity & Tolerance Analysis"),
                    tr("The project has been changed, do you want to save it?"),
                    QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
    switch (tmp.exec()) {
    case QMessageBox::Yes :
        if(!dat.saveData()) {
            ZtLog log;
            dat.logger.pop(log);
            QMessageBox::critical(this,this->windowTitle(),log.content);
            event->ignore();
            break;
        }
    case QMessageBox::No :
        event->accept();
        break;
    default:
        event->ignore();
        break;
    }
}

void MainWindow::on_actionNew_triggered()
{
    if(createFile())
        refresh();
}

void MainWindow::on_actionSave_triggered()
{
    if(!dat.saveData()) {
        ZtLog log;
        dat.logger.pop(log);
        QMessageBox::critical(this,this->windowTitle(),log.content);
    }
}

void MainWindow::on_actionSaveAs_triggered()
{
    QFileDialog tmp(this,tr("Select a new store location..."));
    tmp.setFileMode(QFileDialog::AnyFile);
    tmp.setAcceptMode(QFileDialog::AcceptSave);
    tmp.setNameFilter(tr("Sensitivity & Tolerance Analysis project file (*.tol)"));
    QString ftype = ".tol";

    if(tmp.exec() == QDialog::Accepted) {
        QString fn = tmp.selectedFiles()[0];
        if(fn.right(ftype.length())!=ftype) fn += ftype;
        QFileInfo f(fn);
        if(!dat.changeLocation(f.absoluteFilePath())) {
            ZtLog log;
            dat.logger.pop(log);
            QMessageBox::critical(this,this->windowTitle(),log.content);
        }
    }
}

void MainWindow::on_actionSave_copy_as_triggered()
{
    QFileDialog tmp(this,tr("Select the location for the copy..."));
    tmp.setFileMode(QFileDialog::AnyFile);
    tmp.setAcceptMode(QFileDialog::AcceptSave);
    tmp.setNameFilter(tr("Sensitivity & Tolerance Analysis project file (*.tol)"));
    QString ftype = ".tol";

    if(tmp.exec() == QDialog::Accepted) {
        QString fn = tmp.selectedFiles()[0];
        if(fn.right(ftype.length())!=ftype) fn += ftype;
        QFileInfo f(fn);
        if(!dat.saveCopy(f.absoluteFilePath())) {
            ZtLog log;
            dat.logger.pop(log);
            QMessageBox::critical(this,this->windowTitle(),log.content);
        }
    }
}

void MainWindow::on_actionOpen_triggered()
{
    if (openFile())
        refresh();
}
