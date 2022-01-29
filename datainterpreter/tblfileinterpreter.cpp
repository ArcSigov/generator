#include "tblfileinterpreter.h"
#include "tablerowprop.h"
TblDataInterpreter::TblDataInterpreter(QVector<DataStorage>* s,QObject* parent) :
    FileDataInterpreter(parent) ,
    v(s)
{

}

TblDataInterpreter::~TblDataInterpreter()
{

}

void TblDataInterpreter::readFileData(const QStringList &l)
{
    for (const auto& it:l)
    {
        auto list = it.split(";");
        DataStorage d;
        for (auto i = 0 ; i < list.size(); i++)
            d.set(list.at(i),i);
        v->push_back(d);
    }
}

QStringList TblDataInterpreter::interpreteToFileData()
{
    if( !v) return{};

    QStringList data;
    for (auto it = v->begin(); it != v->end() ; it++)
    {
        QString str;
        for (auto i = 0 ; i < COLUMN_COUNT; i++)
        {
            str += it->at(i).toString() + ";";
        }
        data.push_back(str+"\r\n");
    }
    return data;
}
