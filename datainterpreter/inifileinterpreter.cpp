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

void IniDataInterpreter::readFileData(const QStringList &l)
{








}

QStringList IniDataInterpreter::interpreteToFileData()
{
    if(!v) return{};
    QStringList list;
    for (auto it = v->begin(); it!= v->end(); it++)
    {
        QString formatted;
        formatted.push_back("00000000\n");
        formatted.push_back(it->genericSize() + "\n");
        formatted.push_back(it->at(FILE_PATH).toString()+"\n");
        formatted.push_back(it->genericName()+"\n"+" "+"\n");
        formatted.push_back(it->at(DESCRIPTION).toString()+"\n");
        formatted.push_back(it->at(VERSION).toString() + " " + it->at(REVISION).toString() + "\n");
        list.push_back(formatted);        
    }
    return list;
}

