#include "inifileinterpreter.h"

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
    for (const auto& it:l)
    {
        DataStorage d;
        for (auto i = 0 ; i < it.size(); i++)
            d.set(it.at(i),i);
        v->push_back(d);
    }
}

QStringList IniDataInterpreter::interpreteToFileData()
{
    if( !v)
        return{};


    return {};
}
