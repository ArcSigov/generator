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
        v->push_back(DataStorage());
    }

    emit dataUpdated(true);
}
