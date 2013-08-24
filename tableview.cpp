#include "tableview.h"

TableView::TableView(ZtTable *_dat, QWidget *parent):QTableWidget((QWidget *)parent)
{
    type = 0;
    dat = _dat;

    setColumnCount(dat->Header().length());
    setHorizontalHeaderLabels(dat->Header());

    setWindowModified(false);
    refresh();
}

void TableView::refresh() {
    for(int i=rowCount();i>0;i--)
        removeRow(i-1);

    QTableWidgetItem item;
    QBrush *brush = new QBrush(Qt::white);
    item.setFlags(Qt::ItemIsEnabled|Qt::ItemIsSelectable);
    item.setBackground(*brush);

    for(int i=0;i<dat->rowsLength();i++) {
        insertRow(i);
        setVerticalHeaderItem(i,new QTableWidgetItem(QString::number(i+1)));
        for(int j=0;j<dat->Header().length();j++) {
            item.setText(dat->rowsAt(i)[j]);
            setItem(i,j,new QTableWidgetItem(item));
        }
    }
}
