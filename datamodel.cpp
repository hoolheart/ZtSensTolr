#include "datamodel.h"
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QStringList>

DataModel::DataModel() {
    isLoad = false;
    isModified = false;
    fileName = QString();
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
                if(!_dat->loadXml(reader)) {
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
        fileName = filename;
        return true;
    }
}

bool DataModel::storeData(QString filename) {
    if(!isLoad) {
        logger.reportError(tr("Attempt to store before load"));
        return false;
    }

    QFile file(filename);
    if(!file.open(QFile::WriteOnly|QFile::Text|QFile::Truncate)) {
        logger.reportError(tr("Fail to open the file ")+filename);
        return false;
    }

    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.setCodec("UTF-8");
    writer.writeStartDocument();
    dat->saveXml(writer);
    writer.writeEndDocument();

    file.close();
    if(file.error()) {
        logger.reportError(tr("Error when writing the file ")+filename
                           +tr(" with error code ")+QString::number(file.error()));
        return false;
    }
    isModified = false;
    return true;
}

int DataModel::checkComponentId(QString _id) {
    int i;
    for(i=0;i<dat->componentsLength();i++) {
        if (dat->componentsAt(i)->Id()==_id)
            break;
    }
    if (i<dat->componentsLength())
        return i;
    else
        return -1;
}

bool DataModel::addComponent(QString _id, QString _name, double _value, QString _unit, QString _des) {
    if(!isLoad) {
        logger.reportError(tr("Attempt to modify before load"));
        return false;
    }

    if(checkComponentId(_id)+1) {
        logger.reportError(tr("Component Id ")+_id+tr(" has existed"));
        return false;
    }
    Component *c = new Component();
    c->setId(_id); c->setName(_name); c->setValue(_value); c->setUnit(_unit); c->setDescription(_des);
    dat->addComponent(c);

    isModified = true;
    return true;
}

bool DataModel::modifyComponent(QString id, QString attr, QString value) {
    if(!isLoad) {
        logger.reportError(tr("Attempt to modify before load"));
        return false;
    }

    int i=checkComponentId(id);
    if(i+1) {
        if (attr=="Id") {
            if(checkComponentId(value)) {
                logger.reportError(tr("Component Id ")+value+tr(" has existed"));
                return false;
            }
            dat->componentsAt(i)->setId(value);
        }
        else if (attr=="Name") {
            dat->componentsAt(i)->setName(value);
        }
        else if (attr=="Value") {
            dat->componentsAt(i)->setValue(value.toDouble());
        }
        else if (attr=="Unit") {
            dat->componentsAt(i)->setUnit(value);
        }
        else if (attr=="Description") {
            dat->componentsAt(i)->setDescription(value);
        }
        else {
            logger.reportError(tr("Components have no such attribute as ")+attr);
            return false;
        }
        isModified = true;
        return true;
    }
    else {
        logger.reportError(tr("Component Id ")+id+tr(" does not exist"));
        return false;
    }
}

bool DataModel::deleteComponent(QString id) {
    if(!isLoad) {
        logger.reportError(tr("Attempt to modify before load"));
        return false;
    }

    int i=checkComponentId(id);
    if(i+1) {
        dat->delComponent(i);
        isModified = true;
        return true;
    }
    else {
        logger.reportError(tr("Component Id ")+id+tr(" does not exist"));
        return false;
    }
}

void DataModel::updateComponents() {
    if(!isLoad) {
        logger.reportWarning(tr("Attempt to show data before load"));
        return;
    }

    components.cleanAll();
    components.setHeader(QString("Id,Name,Value,Unit,Description").split(','));
    for(int i=0;i<dat->componentsLength();i++) {
        Component *c = dat->componentsAt(i);
        QStringList r;
        r.append(c->Id());
        r.append(c->Name());
        r.append(QString::number(c->Value()));
        r.append(c->Unit());
        r.append(c->Description());
        components.addRow(r);
    }
}

int DataModel::checkFeatureId(QString _id) {
    int i;
    for(i=0;i<dat->featuresLength();i++) {
        if (dat->featuresAt(i)->Id()==_id)
            break;
    }
    if (i<dat->featuresLength())
        return i;
    else
        return -1;
}

bool DataModel::addFeature(QString _id, QString _name, QString _unit, QString _des) {
    if(!isLoad) {
        logger.reportError(tr("Attempt to modify before load"));
        return false;
    }

    if(checkFeatureId(_id)+1) {
        logger.reportError(tr("Feature Id ")+_id+tr(" has existed"));
        return false;
    }
    Feature *f = new Feature();
    f->setId(_id); f->setName(_name); f->setUnit(_unit); f->setDescription(_des);
    dat->addFeature(f);

    isModified = true;
    return true;
}

bool DataModel::modifyFeature(QString id, QString attr, QString value) {
    if(!isLoad) {
        logger.reportError(tr("Attempt to modify before load"));
        return false;
    }

    int i=checkFeatureId(id);
    if(i+1) {
        if (attr=="Id") {
            if(checkFeatureId(value)) {
                logger.reportError(tr("Feature Id ")+value+tr(" has existed"));
                return false;
            }
            dat->featuresAt(i)->setId(value);
        }
        else if (attr=="Name") {
            dat->featuresAt(i)->setName(value);
        }
        else if (attr=="Unit") {
            dat->featuresAt(i)->setUnit(value);
        }
        else if (attr=="Description") {
            dat->featuresAt(i)->setDescription(value);
        }
        else {
            logger.reportError(tr("Features have no such attribute as ")+attr);
            return false;
        }
        isModified = true;
        return true;
    }
    else {
        logger.reportError(tr("Feature Id ")+id+tr(" does not exist"));
        return false;
    }
}

bool DataModel::deleteFeature(QString id) {
    if(!isLoad) {
        logger.reportError(tr("Attempt to modify before load"));
        return false;
    }

    int i=checkFeatureId(id);
    if(i+1) {
        dat->delFeature(i);
        isModified = true;
        return true;
    }
    else {
        logger.reportError(tr("Feature Id ")+id+tr(" does not exist"));
        return false;
    }
}

void DataModel::updateFeatures() {
    if(!isLoad) {
        logger.reportWarning(tr("Attempt to show data before load"));
        return;
    }

    features.cleanAll();
    features.setHeader(QString("Id,Name,Unit,Description").split(','));
    for(int i=0;i<dat->featuresLength();i++) {
        Feature *f = dat->featuresAt(i);
        QStringList r;
        r.append(f->Id());
        r.append(f->Name());
        r.append(f->Unit());
        r.append(f->Description());
        features.addRow(r);
    }
}

bool DataModel::generateOrthogonalTable() {
    return false;
}

bool DataModel::fillOrthogonalExpriment(int i, QStringList values) {
    if(!isLoad) {
        logger.reportError(tr("Attempt to modify before load"));
        return false;
    }

    if(i<0 || i>=dat->Orthplan_data()->Components()->rowsLength()) {
        logger.reportError(tr("The index ")+QString::number(i)+tr(" does not exist"));
        return false;
    }

    if(values.length()!=dat->Orthplan_data()->Features()->Header().length()) {
        logger.reportError(tr("The number of results do not match the number of features"));
        return false;
    }

    dat->Orthplan_data()->Features()->changeRow(i,values);
    return true;
}

bool DataModel::clearOrthogonalExpriment(int i) {
    if(!isLoad) {
        logger.reportError(tr("Attempt to modify before load"));
        return false;
    }

    if(i<0 || i>=dat->Orthplan_data()->Components()->rowsLength()) {
        logger.reportError(tr("The index ")+QString::number(i)+tr(" does not exist"));
        return false;
    }

    QStringList r;
    for(int k=0;k<dat->Orthplan_data()->Features()->Header().length();k++)
        r.append(tr(""));
    dat->Orthplan_data()->Features()->changeRow(i,r);
    return true;
}

void DataModel::updateOrthogonalTable() {
    if(!isLoad) {
        logger.reportWarning(tr("Attempt to show data before load"));
        return;
    }

    orthogonalTable.cleanAll();
    QStringList t;
//    t.append(tr("Index"));
    t.append(dat->Orthplan_data()->Components()->Header());
    t.append(dat->Orthplan_data()->Features()->Header());
    orthogonalTable.setHeader(t);
    for(int i=0;i<dat->Orthplan_data()->Components()->rowsLength();i++) {
        t.clear();
//        t.append(QString::number(i+1));
        t.append(dat->Orthplan_data()->Components()->rowsAt(i));
        t.append(dat->Orthplan_data()->Features()->rowsAt(i));
        orthogonalTable.addRow(t);
    }
}
