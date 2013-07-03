#include "tolrdata.h"

Orthplan::Orthplan()
{cleanAll();}

Orthplan::~Orthplan()
{cleanAll();}

void Orthplan::cleanAll()
{
    components.clearAll();
    features.clearAll();
    status.clear();
}

bool Orthplan::load(QXmlStreamReader &reader)
{
    cleanAll();

    if(reader.isEndElement()) return false;
    reader.readNext();
    while(!reader.isEndElement()) {
        if(reader.isStartElement()) {
            if(reader.name()=="Components") {
                if(flag0) {flag0=false;break;}
                flag0=true;
                if(!components.load(reader)) {
                    cleanAll();
                    return false;
                }
                reader.readNext();
            }
            else if(reader.name()=="Features") {
                if(flag1) {flag1=false;break;}
                flag1=true;
                if(!features.load(reader)) {
                    cleanAll();
                    return false;
                }
                reader.readNext();
            }
            else if(reader.name()=="Status") {
                QString tmp=reader.readElementText().trimmed();
                bool tmpBool=((tmp=="true") || (tmp=="True") || (tmp=="T") || (tmp=="1"));
                status.append(tmpBool);
                reader.readNext();
            }
            else {cleanAll(); return false;}
        }
        else reader.readNext();
    }

    return true;
}

void Orthplan::save(QXmlStreamWriter &writer)
{
    writer.writeStartElement("Orthplan");

    writer.writeStartElement("Components");
    components.save(writer);
    writer.writeEndElement();
    writer.writeStartElement("Features");
    features.save(writer);
    writer.writeEndElement();
    for(int i=0;i<status.length();i++)
        writer.writeTextElement("Status", status[i]?"True":"False");

    writer.writeEndElement();
}

Feature::Feature()
{cleanAll();}

Feature::~Feature()
{cleanAll();}

void Feature::cleanAll()
{
    id="";
    name="";
    unit="";
    description="";
}

bool Feature::load(QXmlStreamReader &reader)
{
    bool flag0=false; bool flag1=false; bool flag2=false;
    bool flag3=false;
    cleanAll();

    if(reader.isEndElement()) return false;
    reader.readNext();
    while(!reader.isEndElement()) {
        if(reader.isStartElement()) {
            if(reader.name()=="Id") {
                if(flag0) {flag0=false;break;}
                flag0=true;
                id=reader.readElementText().trimmed();
                reader.readNext();
            }
            else if(reader.name()=="Name") {
                if(flag1) {flag1=false;break;}
                flag1=true;
                name=reader.readElementText().trimmed();
                reader.readNext();
            }
            else if(reader.name()=="Unit") {
                if(flag2) {flag2=false;break;}
                flag2=true;
                unit=reader.readElementText().trimmed();
                reader.readNext();
            }
            else if(reader.name()=="Description") {
                if(flag3) {flag3=false;break;}
                flag3=true;
                description=reader.readElementText().trimmed();
                reader.readNext();
            }
            else {cleanAll(); return false;}
        }
        else reader.readNext();
    }

    if(flag0&&flag1&&flag2&&flag3)
        return true;
    else {cleanAll(); return false;}
}

void Feature::save(QXmlStreamWriter &writer)
{
    writer.writeStartElement("Feature");

    writer.writeTextElement("Id", id);
    writer.writeTextElement("Name", name);
    writer.writeTextElement("Unit", unit);
    writer.writeTextElement("Description", description);

    writer.writeEndElement();
}

Component::Component()
{cleanAll();}

Component::~Component()
{cleanAll();}

void Component::cleanAll()
{
    id="";
    name="";
    value=0;
    unit="";
    description="";
}

bool Component::load(QXmlStreamReader &reader)
{
    bool flag0=false; bool flag1=false; bool flag2=false;
    bool flag3=false; bool flag4=false;
    cleanAll();

    if(reader.isEndElement()) return false;
    reader.readNext();
    while(!reader.isEndElement()) {
        if(reader.isStartElement()) {
            if(reader.name()=="Id") {
                if(flag0) {flag0=false;break;}
                flag0=true;
                id=reader.readElementText().trimmed();
                reader.readNext();
            }
            else if(reader.name()=="Name") {
                if(flag1) {flag1=false;break;}
                flag1=true;
                name=reader.readElementText().trimmed();
                reader.readNext();
            }
            else if(reader.name()=="Value") {
                if(flag2) {flag2=false;break;}
                flag2=true;
                value=reader.readElementText().trimmed().toDouble();
                reader.readNext();
            }
            else if(reader.name()=="Unit") {
                if(flag3) {flag3=false;break;}
                flag3=true;
                unit=reader.readElementText().trimmed();
                reader.readNext();
            }
            else if(reader.name()=="Description") {
                if(flag4) {flag4=false;break;}
                flag4=true;
                description=reader.readElementText().trimmed();
                reader.readNext();
            }
            else {cleanAll(); return false;}
        }
        else reader.readNext();
    }

    if(flag0&&flag1&&flag2&&flag3&&flag4)
        return true;
    else {cleanAll(); return false;}
}

void Component::save(QXmlStreamWriter &writer)
{
    writer.writeStartElement("Component");

    writer.writeTextElement("Id", id);
    writer.writeTextElement("Name", name);
    writer.writeTextElement("Value", QString::number(value));
    writer.writeTextElement("Unit", unit);
    writer.writeTextElement("Description", description);

    writer.writeEndElement();
}

ModifiedTime::ModifiedTime()
{cleanAll();}

ModifiedTime::~ModifiedTime()
{cleanAll();}

void ModifiedTime::cleanAll()
{
}

bool ModifiedTime::load(QXmlStreamReader &reader)
{
    cleanAll();

    if(reader.isEndElement()) return false;
    reader.readNext();
    while(!reader.isEndElement()) {
        if(reader.isStartElement()) {
            if(reader.name()=="Component") {
                if(flag0) {flag0=false;break;}
                flag0=true;
                component=QDateTime::fromString(reader.readElementText().trimmed(),"yyyy.MM.dd hh:mm:ss.zzz");
                reader.readNext();
            }
            else if(reader.name()=="Feature") {
                if(flag1) {flag1=false;break;}
                flag1=true;
                feature=QDateTime::fromString(reader.readElementText().trimmed(),"yyyy.MM.dd hh:mm:ss.zzz");
                reader.readNext();
            }
            else if(reader.name()=="Orth") {
                if(flag2) {flag2=false;break;}
                flag2=true;
                orth=QDateTime::fromString(reader.readElementText().trimmed(),"yyyy.MM.dd hh:mm:ss.zzz");
                reader.readNext();
            }
            else if(reader.name()=="Sens") {
                if(flag3) {flag3=false;break;}
                flag3=true;
                sens=QDateTime::fromString(reader.readElementText().trimmed(),"yyyy.MM.dd hh:mm:ss.zzz");
                reader.readNext();
            }
            else {cleanAll(); return false;}
        }
        else reader.readNext();
    }

    return true;
}

void ModifiedTime::save(QXmlStreamWriter &writer)
{
    writer.writeStartElement("ModifiedTime");

    writer.writeTextElement("Component", component.toString("yyyy.MM.dd hh:mm:ss.zzz"));
    writer.writeTextElement("Feature", feature.toString("yyyy.MM.dd hh:mm:ss.zzz"));
    writer.writeTextElement("Orth", orth.toString("yyyy.MM.dd hh:mm:ss.zzz"));
    writer.writeTextElement("Sens", sens.toString("yyyy.MM.dd hh:mm:ss.zzz"));

    writer.writeEndElement();
}

Info::Info()
{cleanAll();}

Info::~Info()
{cleanAll();}

void Info::cleanAll()
{
    name="";
    team="";
    description="";
    modifiedtime.clearAll();
}

bool Info::load(QXmlStreamReader &reader)
{
    bool flag0=false; bool flag1=false; bool flag2=false;
    bool flag4=false;
    cleanAll();

    if(reader.isEndElement()) return false;
    reader.readNext();
    while(!reader.isEndElement()) {
        if(reader.isStartElement()) {
            if(reader.name()=="Name") {
                if(flag0) {flag0=false;break;}
                flag0=true;
                name=reader.readElementText().trimmed();
                reader.readNext();
            }
            else if(reader.name()=="Team") {
                if(flag1) {flag1=false;break;}
                flag1=true;
                team=reader.readElementText().trimmed();
                reader.readNext();
            }
            else if(reader.name()=="Description") {
                if(flag2) {flag2=false;break;}
                flag2=true;
                description=reader.readElementText().trimmed();
                reader.readNext();
            }
            else if(reader.name()=="CreatedTime") {
                if(flag3) {flag3=false;break;}
                flag3=true;
                createdtime=QDateTime::fromString(reader.readElementText().trimmed(),"yyyy.MM.dd hh:mm:ss.zzz");
                reader.readNext();
            }
            else if(reader.name()=="ModifiedTime") {
                if(flag4) {flag4=false;break;}
                flag4=true;
                if(!modifiedtime.load(reader)) {
                    cleanAll();
                    return false;
                }
                reader.readNext();
            }
            else {cleanAll(); return false;}
        }
        else reader.readNext();
    }

    if(flag0&&flag1&&flag2&&flag4)
        return true;
    else {cleanAll(); return false;}
}

void Info::save(QXmlStreamWriter &writer)
{
    writer.writeStartElement("Info");

    writer.writeTextElement("Name", name);
    writer.writeTextElement("Team", team);
    writer.writeTextElement("Description", description);
    writer.writeTextElement("CreatedTime", createdtime.toString("yyyy.MM.dd hh:mm:ss.zzz"));
    modifiedtime.save(writer);

    writer.writeEndElement();
}

Project::Project()
{cleanAll();}

Project::~Project()
{cleanAll();}

void Project::cleanAll()
{
    info.clearAll();
    for(int i=0;i<components.length();i++) delete components[i];
    components.clear();
    for(int i=0;i<features.length();i++) delete features[i];
    features.clear();
    orthplan.clearAll();
    senstable.clearAll();
}

bool Project::load(QXmlStreamReader &reader)
{
    bool flag0=false; bool flag3=false;
    cleanAll();

    if(reader.isEndElement()) return false;
    reader.readNext();
    while(!reader.isEndElement()) {
        if(reader.isStartElement()) {
            if(reader.name()=="Info") {
                if(flag0) {flag0=false;break;}
                flag0=true;
                if(!info.load(reader)) {
                    cleanAll();
                    return false;
                }
                reader.readNext();
            }
            else if(reader.name()=="Component") {
                Component *p=new Component();
                if(p->load(reader))
                    components.append(p);
                else {
                    delete p;
                    cleanAll();
                    return false;
                }
                reader.readNext();
            }
            else if(reader.name()=="Feature") {
                Feature *p=new Feature();
                if(p->load(reader))
                    features.append(p);
                else {
                    delete p;
                    cleanAll();
                    return false;
                }
                reader.readNext();
            }
            else if(reader.name()=="Orthplan") {
                if(flag3) {flag3=false;break;}
                flag3=true;
                if(!orthplan.load(reader)) {
                    cleanAll();
                    return false;
                }
                reader.readNext();
            }
            else if(reader.name()=="Senstable") {
                if(flag4) {flag4=false;break;}
                flag4=true;
                if(!senstable.load(reader)) {
                    cleanAll();
                    return false;
                }
                reader.readNext();
            }
            else {cleanAll(); return false;}
        }
        else reader.readNext();
    }

    if(flag0&&flag3)
        return true;
    else {cleanAll(); return false;}
}

void Project::save(QXmlStreamWriter &writer)
{
    writer.writeStartElement("Project");

    info.save(writer);
    for(int i=0;i<components.length();i++)
        components[i]->save(writer);
    for(int i=0;i<features.length();i++)
        features[i]->save(writer);
    orthplan.save(writer);
    writer.writeStartElement("Senstable");
    senstable.save(writer);
    writer.writeEndElement();

    writer.writeEndElement();
}
