#include "inifileinterpreter.h"
#include "tablerowprop.h"
IniDataInterpreter::IniDataInterpreter(QVector<DataStorage>* s,QObject* parent) :
    FileDataInterpreter(parent) ,
    v(s)
{

}

IniDataInterpreter::~IniDataInterpreter()
{

}

void IniDataInterpreter::read()
{

}

void IniDataInterpreter::write()
{
    if(!v) return;
    m->setFilePath("conf.ini");
    for (auto it = v->begin(); it!= v->end(); it++)
    {
        QString formatted;
        formatted.push_back("00000000\r\n");
        formatted.push_back(it->genericSize() + "\r\n");
        formatted.push_back(it->at(FILE_PATH).toString()+"\r\n");
        formatted.push_back(it->genericName()+"\r\n"+" "+"\r\n");
        formatted.push_back(it->at(DESCRIPTION).toString()+"\r\n");
        formatted.push_back(it->at(VERSION).toString() + " " + it->at(REVISION).toString() + "\r\n");
        m->write(QStringList(formatted));
    }
}
