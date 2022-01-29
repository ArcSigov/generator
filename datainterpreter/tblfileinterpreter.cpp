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

void TblDataInterpreter::readFileData(const QVector<QStringList> &l)
{
    if (l.empty())
        emit dataFromFileCompleted(false);

    for (const auto& it:l)
    {
        DataStorage d;
        for (auto i = 0 ; i < it.size(); i++)
            d.set(it.at(i),i);
        v->push_back(d);
    }
    emit dataFromFileCompleted(true);
}

void TblDataInterpreter::interpreteToFileData(bool flag)
{
    if(!flag || !v)
        return;

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
    emit dataToFileCompleted(data);
}
