#ifndef DATAMODEL_H
#define DATAMODEL_H
#include <QString>
#include "tolrdata.h"
#include "ztlogger.h"

class DataModel
{
    Q_OBJECT

private:
    Project *dat;
    bool isLoad, isModified;
public:
    ZtLogger logger;
    DataModel();
    ~DataModel();

    // load or store the data form or to file
    bool loadData(QString filename);
    bool storeData(QString filename);

    // actions
    // for components
    bool addComponent(QString _id, QString _name, double _value, QString _unit="", QString _des="");
    bool modifyComponent(QString id, QString attr, QString value);
    bool deleteComponent(QString id);
};

#endif // DATAMODEL_H
