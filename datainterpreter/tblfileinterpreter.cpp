#include "tblfileinterpreter.h"
#include "tablerowprop.h"


TblDataInterpreter::TblDataInterpreter(QVector<DataStorage>* s) :
    v(s)
{

}

void TblDataInterpreter::read()
{
    auto tbldata = m->read();
    for (const auto& it:tbldata)
    {
        auto list = it.split(";");
        DataStorage d;
        for (auto i = 0 ; i < list.size(); i++)
            d.set(list.at(i),i);
        v->push_back(d);
    }
}

void TblDataInterpreter::write([[maybe_unused]] const DataStorage& storage)
{
    if( !v) return;

    QStringList data;
    for (auto it = v->begin(); it != v->end() ; it++)
    {
        if (it != v->begin()) data.push_back("\r\n");

        QString str;
        for (auto i = 0 ; i < COLUMN_COUNT; i++)
        {
            str += it->at(i).toString() + ";";
        }
        data.push_back(str);
    }
    m->write(data);
}
