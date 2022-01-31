#include "butchinterpreter.h"
#include "tablerowprop.h"
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

//                     (QDir::currentPath().toStdString() + "/out/ini") +
//                     (table->item(i,FILE_TYPE)->text() == "Бинарный" ?   " -bs " :" ")   +
//                     (table->item(i,FILE_DATE)->text().isEmpty() ? " " : "-d " + table->item(i,FILE_DATE)->text().toStdString()+" ") +
//                     (table->item(i,FILE_CRC)->text().isEmpty() ? " "  : "-cs " + table->item(i,FILE_CRC)->text().toStdString()+" ") +
//                     (" > " + QDir::currentPath().toStdString() + "/out/log.crc")).c_str());

void ButchInterpreter::write()
{
    if(!v) return;

    for (auto it = v->begin(); it!= v->end(); it++)
    {
        QString formatted;




        m->write(QStringList(formatted));
    }
}
