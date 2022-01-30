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

void ButchInterpreter::readFileData(const QStringList &l)
{
    Q_UNUSED(l);
}

//                     (QDir::currentPath().toStdString() + "/out/ini") +
//                     (table->item(i,FILE_TYPE)->text() == "Бинарный" ?   " -bs " :" ")   +
//                     (table->item(i,FILE_DATE)->text().isEmpty() ? " " : "-d " + table->item(i,FILE_DATE)->text().toStdString()+" ") +
//                     (table->item(i,FILE_CRC)->text().isEmpty() ? " "  : "-cs " + table->item(i,FILE_CRC)->text().toStdString()+" ") +
//                     (" > " + QDir::currentPath().toStdString() + "/out/log.crc")).c_str());

QStringList ButchInterpreter::interpreteToFileData()
{
    if(!v) return{};
    QStringList list;
    for (auto it = v->begin(); it!= v->end(); it++)
    {
        QString formatted;

        list.push_back(formatted);        
    }
    return list;
}
