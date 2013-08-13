#include "datamodel.h"
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

DataModel::DataModel() {
    isLoad = false;
    isModified = true;
}

DataModel::~DataModel() {
    if (isLoad)
        delete dat;
}

bool DataModel::loadData(QString filename) {
    if(!QFile::exists(filename)) {
        logger.reportError(tr("File ")+filename+tr(" does not exist"));
        return false;
    }
    QFile file(filename);
    if(!file.open(QFile::ReadOnly|QFile::Text)) {
        logger.reportError(tr("Fail to open the file ")+filename);
        return false;
    }
    QXmlStreamReader reader(&file);

    Project *_dat = new Project();
    bool hasError = false;
    reader.readNext();
    while(!reader.atEnd()) {
        if(reader.isStartElement()) {
            if(reader.name() == "Project") {
                if(!_dat->load(reader)) {
                    logger.reportError(tr("Format of the file ")+filename+tr(" is wrong"));
                    hasError = true;
                    break;
                }
                reader.readNext();
            }
            else {
                logger.reportError(tr("Format of the file ")+filename+tr(" is wrong"));
                hasError = true;
                break;
            }
        }
        else
            reader.readNext();
    }

    file.close();

    if(hasError) {
        delete _dat;
        return false;
    }
    else {
        if (isLoad)
            delete dat;
        dat = _dat;
        isLoad = true;
        return true;
    }
}

bool DataModel::storeData(QString filename) {
    return false;
}

bool DataModel::addComponent(QString _id, QString _name, double _value, QString _unit, QString _des) {
    return false;
}

bool DataModel::modifyComponent(QString id, QString attr, QString value) {
    return false;
}

bool DataModel::deleteComponent(QString id) {
    return false;
}
