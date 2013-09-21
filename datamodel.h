#ifndef DATAMODEL_H
#define DATAMODEL_H
#include <QString>
#include "tolrdata.h"
#include "ztlogger.h"
#include "ZtTable.h"
#include "stmath.h"

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

    // create, load or store the data form or to file
    void createData(QString name, QString team, QString des, QString filename);
    bool loadData(QString filename);
    bool saveData();
    bool changeLocation(QString filename);
    bool saveCopy(QString filename);
private:
    bool storeData(QString filename);

public:
    // actions
    void updateAll();
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
    bool generateOrthogonalTable(int level, double err);
    bool fillOrthogonalExpriment(int i, QStringList values);
    bool clearOrthogonalExpriment(int i);
    void updateOrthogonalTable();
};

#endif // DATAMODEL_H
