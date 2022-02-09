#include "batchprocessor.h"
#include <QDir>

BatchProcessor::BatchProcessor() :
    cur_id_path(QDir::currentPath() + "/ID_Info_con.exe " + QDir::currentPath() + "/conf.ini "),
    result_path(" > " + QDir::currentPath() + "/log.ini")
{

}

/*!
Выполняет генерацию флагов работы программы Id_Info_Con.exe и передает его менеджеру командной строки на выполнение
*/
void BatchProcessor::process()
{
    QString formatted = cur_id_path;
    for (auto it = s->begin(); it != s->end(); it++)
    {
        auto crc = it->at(CRC).toUInt();
        auto date = it->at(ID_DATE).toDate().toString(Qt::SystemLocaleShortDate).replace(".",":");

        formatted.push_back(it->genericType() ? " " : "-bs ");
        formatted.push_back(date.isEmpty() ? " " : " -d " + date);
        formatted.push_back(crc > 0  ? "-cs " + it->at(CRC).toString(): " ");
        formatted.push_back(result_path);
    }
    m->write(QStringList(formatted));
}
