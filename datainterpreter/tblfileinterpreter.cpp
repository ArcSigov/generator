#include "tblfileinterpreter.h"

TblFileInterpreter::TblFileInterpreter(QVector<DataStorage>* s,QObject* parent) : FileDataInterpreter(parent) , v(s)
{

}

TblFileInterpreter::~TblFileInterpreter()
{

}

void TblFileInterpreter::readFileData(const QVector<QStringList> &l)
{
    if (l.empty())
        emit dataUpdated(false);

    for (const auto& it:l)
    {
        DataStorage d;
        for (auto i = 0 ; i < it.size(); i++)
            d.SetValue(it.at(i),i);
        v->push_back(d);
    }

    emit dataUpdated(true);
}
