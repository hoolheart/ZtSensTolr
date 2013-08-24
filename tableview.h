#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QTableWidget>
#include "ZtTable.h"

class TableView : public QTableWidget
{
private:
    int type; // reserved
    ZtTable *dat; // table content
public:
    TableView(ZtTable *_dat, QWidget *parent=0);
    void refresh();
};

#endif // TABLEVIEW_H
