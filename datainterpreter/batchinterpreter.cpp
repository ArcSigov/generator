#include "batchinterpreter.h"
#include "tablerowprop.h"
#include <QDir>

BatchInterpreter::BatchInterpreter()
{
    cur_id_path = QDir::currentPath() + "/ID_Info_con.exe " + QDir::currentPath() + "/conf.ini ";
    result_path = " > " + QDir::currentPath() + "/log.ini";
}

void BatchInterpreter::write(const DataStorage& storage)
{
    QString formatted = cur_id_path;
    auto crc = storage.at(CRC).toInt();
    auto date = storage.at(ID_DATE).toDate().toString(Qt::SystemLocaleShortDate).replace(".",":");

    formatted.push_back(storage.genericType() ? " " : "-bs ");
    formatted.push_back(date.isEmpty() ? " " : " -d " + date);
    formatted.push_back(crc > 0  ? "-cs " + storage.at(CRC).toString(): " ");
    formatted.push_back(result_path);
    m->write(QStringList(formatted));
}
