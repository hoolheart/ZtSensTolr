#include "datamodel.h"
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QStringList>

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

int DataModel::checkComponentIdExisted(QString _id) {
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

    if(checkComponentIdExisted(_id)+1) {
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

    int i=checkComponentIdExisted(id);
    if(i+1) {
        if (attr=="Id") {
            if(checkComponentIdExisted(value)) {
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

    int i=checkComponentIdExisted(id);
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

bool DataModel::generateOrthogonalTable() {
    return false;
}
