#ifndef DATAMODEL_H
#define DATAMODEL_H
#include <QString>
#include "tolrdata.h"
#include "ztlogger.h"
#include "ZtTable.h"

class DataModel : public QObject
{
    Q_OBJECT

private:
    Project *dat;
    bool isLoad, isModified;

public:
    ZtLogger logger;
    ZtTable components;

public:
    DataModel();
    ~DataModel();

    // load or store the data form or to file
    bool loadData(QString filename);
    bool storeData(QString filename);

    // actions
    // for components
    int checkComponentIdExisted(QString _id);
    bool addComponent(QString _id, QString _name, double _value, QString _unit="", QString _des="");
    bool modifyComponent(QString id, QString attr, QString value);
    bool deleteComponent(QString id);
    void updateComponents();
    bool generateOrthogonalTable();
};

#endif // DATAMODEL_H
