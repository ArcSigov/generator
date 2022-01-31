#include "butchinterpreter.h"
#include "tablerowprop.h"
#include <QDir>

ButchInterpreter::ButchInterpreter(QVector<DataStorage> *s, QObject* parent) :
    FileDataInterpreter(parent),
    v(s)
{

}

ButchInterpreter::~ButchInterpreter()
{

}

void ButchInterpreter::read()
{
}

void ButchInterpreter::write()
{
    if(!v) return;

    auto cur_id_path = QDir::currentPath() + "/ID_Info_con.exe " + QDir::currentPath() + "/conf.ini ";
    auto out_result = " > " + QDir::currentPath() + "/log.ini";
    for (auto it = v->begin(); it!= v->end(); it++)
    {
        QString formatted = cur_id_path;
        auto crc = it->at(CRC).toInt();
        auto date = it->at(ID_DATE).toDate().toString(Qt::SystemLocaleShortDate).replace(".",":");

        formatted.push_back(it->genericType() ? " " : "-bs ");
        formatted.push_back(date.isEmpty() ? " " : " -d " + date);
        formatted.push_back(crc > 0  ? "-cs " + it->at(CRC).toString() + " " : " ");
        formatted.push_back(out_result);
        m->write(QStringList(formatted));
    }
}
