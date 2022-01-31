#include "batchinterpreter.h"
#include "tablerowprop.h"
#include <QDir>

BatchInterpreter::BatchInterpreter(QObject* parent) :
    FileDataInterpreter(parent)
{

}

BatchInterpreter::~BatchInterpreter()
{

}

void BatchInterpreter::read()
{
}

void BatchInterpreter::write(DataStorage* storage)
{
    if(!storage) return;

    static auto cur_id_path = QDir::currentPath() + "/ID_Info_con.exe " + QDir::currentPath() + "/conf.ini ";
    static auto out_result = " > " + QDir::currentPath() + "/log.ini";

    QString formatted = cur_id_path;
    auto crc = storage->at(CRC).toInt();
    auto date = storage->at(ID_DATE).toDate().toString(Qt::SystemLocaleShortDate).replace(".",":");

    formatted.push_back(storage->genericType() ? " " : "-bs ");
    formatted.push_back(date.isEmpty() ? " " : " -d " + date);
    formatted.push_back(crc > 0  ? "-cs " + storage->at(CRC).toString(): " ");
    formatted.push_back(out_result);
    m->write(QStringList(formatted));

}
