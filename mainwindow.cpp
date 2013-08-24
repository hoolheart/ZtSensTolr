#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    dat.loadData(QString("E:\\Design\\GitHut\\ZtSensTolr\\dat_test1.xml"));
    dat.updateComponents();
    comView = new TableView(&dat.components,this);
    dat.updateFeatures();
    feaView = new TableView(&dat.features,this);
    dat.updateOrthogonalTable();
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
