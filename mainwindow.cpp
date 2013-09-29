#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include "createprodialog.h"
#include "startupdialog.h"
#include "addcomponentdialog.h"
#include "componentdialog.h"
#include "addfeaturedialog.h"
#include "featuredialog.h"

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

//    dat.loadData(QString("E:\\Design\\GitHut\\ZtSensTolr\\dat_test1.tol"));
//    dat.updateAll();
    comView = new TableView(&dat.components,this);
    feaView = new TableView(&dat.features,this);
    orthView = new TableView(&dat.orthogonalTable,this);

    tabs->addTab((QWidget *)comView,tr("Components"));
    tabs->addTab((QWidget *)feaView,tr("Features"));
    tabs->addTab((QWidget *)orthView,tr("Orthogonal Table"));
    tabs->setCurrentWidget((QWidget *)comView);
    controlActions();
    connect(tabs,SIGNAL(currentChanged(int)),this,SLOT(controlActions()));

    connect(comView,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(on_doubleclick_component(QTableWidgetItem*)));
    connect(ui->action_Add_Component,SIGNAL(triggered()),this,SLOT(on_add_component()));
    connect(feaView,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(on_doubleclick_feature(QTableWidgetItem*)));
    connect(ui->action_Add_Feature,SIGNAL(triggered()),this,SLOT(on_add_feature()));

    comView->addAction(ui->action_Add_Component);
    comView->addAction(ui->action_Show_Component);
    comView->addAction(ui->action_Delete_Component);
    comView->setContextMenuPolicy(Qt::ActionsContextMenu);
    feaView->addAction(ui->action_Add_Feature);
    feaView->addAction(ui->action_Show_Feature);
    feaView->addAction(ui->action_Delete_Feature);
    feaView->setContextMenuPolicy(Qt::ActionsContextMenu);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete proTree;
    delete comView; delete feaView; delete orthView;
    delete tabs;
    delete central;
}

void MainWindow::on_actionGOrth_triggered()
{
    dat.generateOrthogonalTable(2,0.05);
    refresh();
}

void MainWindow::controlActions() {
    int i = tabs->currentIndex();

    // disable actions
    ui->menu_Components->setEnabled(false);
    ui->menu_Feature->setEnabled(false);

    // enable available actions
    switch (i) {
    case 0:
        ui->menu_Components->setEnabled(true);
        break;
    case 1:
        ui->menu_Feature->setEnabled(true);
        break;
    default:
        break;
    }
}

bool MainWindow::startup() {
    StartupDialog d(this);
    if (d.exec()==QDialog::Accepted) {
        refresh();
        return true;
    }
    else
        return false;
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

void MainWindow::on_doubleclick_component(QTableWidgetItem *item) {
    int r = item->row();
    if(r<0 || r>=dat.components.rowsLength())
        on_add_component();
    else
        on_show_component(r);
}

void MainWindow::on_add_component() {
    AddComponentDialog d(this);
    if(d.exec()==QDialog::Accepted) {
        if(dat.addComponent(d.id,d.name,d.value,d.unit,d.des)) {
            refresh();
        }
        else {
            ZtLog log;
            dat.logger.pop(log);
            QMessageBox::critical(this,tr("Failed to add component"),log.content);
        }
    }
}

void MainWindow::on_show_component(int i) {
    if(i>=0&&i<dat.components.rowsLength()) {
        ComponentDialog d(dat.components.rowsAt(i),&dat,this);
        d.exec();
        if(dat.IsModified())
            refresh();
    }
}

void MainWindow::on_action_Show_Component_triggered()
{
    QTableWidgetItem * item = comView->currentItem();
    on_show_component(item->row());
}

void MainWindow::on_action_Delete_Component_triggered()
{
    QTableWidgetItem * item = comView->currentItem();
    int i=item->row();
    if(i>=0&&i<dat.components.rowsLength()) {
        if(QMessageBox::question(this,this->windowTitle(),
                                 tr("Do you want to delete the component \"")+dat.components.rowsAt(i)[0]+tr("\"?"))
                ==QMessageBox::Yes) {
            if(dat.deleteComponent(dat.components.rowsAt(i)[0]))
                refresh();
            else {
                ZtLog log;
                dat.logger.pop(log);
                QMessageBox::critical(this,tr("Failed to delete component"),log.content);
            }
        }
    }
}

void MainWindow::on_doubleclick_feature(QTableWidgetItem *item) {
    int r = item->row();
    if(r>=0&&r<dat.features.rowsLength()) {
        FeatureDialog d(dat.features.rowsAt(r),&dat,this);
        d.exec();
        if(dat.IsModified())
            refresh();
    }
}

void MainWindow::on_add_feature() {
    AddFeatureDialog d(this);
    if(d.exec()==QDialog::Accepted) {
        if(dat.addFeature(d.id,d.name,d.unit,d.des)) {
            refresh();
        }
        else {
            ZtLog log;
            dat.logger.pop(log);
            QMessageBox::critical(this,tr("Failed to add feature"),log.content);
        }
    }
}

void MainWindow::on_action_Show_Feature_triggered()
{
    QTableWidgetItem * item = feaView->currentItem();
    on_doubleclick_feature(item);
}

void MainWindow::on_action_Delete_Feature_triggered()
{
    QTableWidgetItem * item = feaView->currentItem();
    int i=item->row();
    if(i>=0&&i<dat.features.rowsLength()) {
        if(QMessageBox::question(this,this->windowTitle(),
                                 tr("Do you want to delete the feature \"")+dat.features.rowsAt(i)[0]+tr("\"?"))
                ==QMessageBox::Yes) {
            if(dat.deleteFeature(dat.features.rowsAt(i)[0]))
                refresh();
            else {
                ZtLog log;
                dat.logger.pop(log);
                QMessageBox::critical(this,tr("Failed to delete feature"),log.content);
            }
        }
    }
}
