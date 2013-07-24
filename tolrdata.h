#ifndef TOLRDATA_H
#define TOLRDATA_H
#include <QStringList>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDateTime>
#include "ZtTable.h"

class Project;
class Info;
class ModifiedTime;
class Component;
class Feature;
class Orthplan;

class Orthplan {
private:
    ZtTable components;
    ZtTable features;
    QList<bool> status;
public:
    Orthplan();
    ~Orthplan();
    ZtTable* Components() {return &components;}
    ZtTable* Features() {return &features;}
    int statusLength() const {return status.length();}
    bool statusAt(int i) const {if(i>=0 && i<status.length()) return status[i]; else return 0;}
    bool delStatus(int i) {if(i>=0 && i<status.length()) {status.removeAt(i);return true;} else return false;}
    bool changeStatus(int i, bool _n) {if(i>=0 && i<status.length()) {status[i]=_n;return true;} else return false;}
    void addStatus(bool _n) {status.append(_n);}
    void cleanAll();
    bool load(QXmlStreamReader &reader);
    void save(QXmlStreamWriter &writer);
};

class Feature {
private:
    QString id;
    QString name;
    QString unit;
    QString description;
public:
    Feature();
    ~Feature();
    QString Id() const {return id;}
    void setId(const QString &_n) {id=_n;}
    QString Name() const {return name;}
    void setName(const QString &_n) {name=_n;}
    QString Unit() const {return unit;}
    void setUnit(const QString &_n) {unit=_n;}
    QString Description() const {return description;}
    void setDescription(const QString &_n) {description=_n;}
    void cleanAll();
    bool load(QXmlStreamReader &reader);
    void save(QXmlStreamWriter &writer);
};

class Component {
private:
    QString id;
    QString name;
    double value;
    QString unit;
    QString description;
public:
    Component();
    ~Component();
    QString Id() const {return id;}
    void setId(const QString &_n) {id=_n;}
    QString Name() const {return name;}
    void setName(const QString &_n) {name=_n;}
    double Value() const {return value;}
    void setValue(double _n) {value=_n;}
    QString Unit() const {return unit;}
    void setUnit(const QString &_n) {unit=_n;}
    QString Description() const {return description;}
    void setDescription(const QString &_n) {description=_n;}
    void cleanAll();
    bool load(QXmlStreamReader &reader);
    void save(QXmlStreamWriter &writer);
};

class ModifiedTime {
private:
    QDateTime component;
    QDateTime feature;
    QDateTime orth;
    QDateTime sens;
public:
    ModifiedTime();
    ~ModifiedTime();
    QDateTime Component() const {return component;}
    void setComponent(const QDateTime &_n) {component=_n;}
    QDateTime Feature() const {return feature;}
    void setFeature(const QDateTime &_n) {feature=_n;}
    QDateTime Orth() const {return orth;}
    void setOrth(const QDateTime &_n) {orth=_n;}
    QDateTime Sens() const {return sens;}
    void setSens(const QDateTime &_n) {sens=_n;}
    void cleanAll();
    bool load(QXmlStreamReader &reader);
    void save(QXmlStreamWriter &writer);
};

class Info {
private:
    QString name;
    QString team;
    QString description;
    QDateTime createdtime;
    ModifiedTime modifiedtime;
public:
    Info();
    ~Info();
    QString Name() const {return name;}
    void setName(const QString &_n) {name=_n;}
    QString Team() const {return team;}
    void setTeam(const QString &_n) {team=_n;}
    QString Description() const {return description;}
    void setDescription(const QString &_n) {description=_n;}
    QDateTime CreatedTime() const {return createdtime;}
    void setCreatedTime(const QDateTime &_n) {createdtime=_n;}
    ModifiedTime* ModifiedTime_data() {return &modifiedtime;}
    void cleanAll();
    bool load(QXmlStreamReader &reader);
    void save(QXmlStreamWriter &writer);
};

class Project {
private:
    Info info;
    QList<Component *> components;
    QList<Feature *> features;
    Orthplan orthplan;
    ZtTable senstable;
public:
    Project();
    ~Project();
    Info* Info_data() {return &info;}
    int componentsLength() const {return components.length();}
    Component* componentsAt(int i) {if(i>=0 && i<components.length()) return components[i]; else return 0;}
    bool delComponent(int i) {if(i>=0 && i<components.length()) {delete components[i];components.removeAt(i);return true;} else return false;}
    void addComponent(Component *_n) {components.append(_n);}
    int featuresLength() const {return features.length();}
    Feature* featuresAt(int i) {if(i>=0 && i<features.length()) return features[i]; else return 0;}
    bool delFeature(int i) {if(i>=0 && i<features.length()) {delete features[i];features.removeAt(i);return true;} else return false;}
    void addFeature(Feature *_n) {features.append(_n);}
    Orthplan* Orthplan_data() {return &orthplan;}
    ZtTable* Senstable() {return &senstable;}
    void cleanAll();
    bool load(QXmlStreamReader &reader);
    void save(QXmlStreamWriter &writer);
};

#endif
