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
    QString fileName;

public:
    ZtLogger logger;
    ZtTable components;
    ZtTable features;
    ZtTable orthogonalTable;

public:
    DataModel();
    ~DataModel();
    QString FileName() const {return fileName;}
    bool IsLoad() const {return isLoad;}
    bool IsModified() const {return isModified;}

    // load or store the data form or to file
    bool loadData(QString filename);
    bool storeData(QString filename);

    // actions
    // for components
    int checkComponentId(QString _id);
    bool addComponent(QString _id, QString _name, double _value, QString _unit="", QString _des="");
    bool modifyComponent(QString id, QString attr, QString value);
    bool deleteComponent(QString id);
    void updateComponents();
    //for features
    int checkFeatureId(QString _id);
    bool addFeature(QString _id, QString _name, QString _unit="", QString _des="");
    bool modifyFeature(QString id, QString attr, QString value);
    bool deleteFeature(QString id);
    void updateFeatures();
    // for orthogonal table
    bool generateOrthogonalTable();
    bool fillOrthogonalExpriment(int i, QStringList values);
    bool clearOrthogonalExpriment(int i);
    void updateOrthogonalTable();
};

#endif // DATAMODEL_H
