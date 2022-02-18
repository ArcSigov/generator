#include "iniprocessor.h"
#include "tablerowprop.h"


/*!
Читает результат выполнения программы ID_Info_Con.exe
\param[out] Qstoragetring результат выполнения программы
*/
QString IniDataProcessor::quittance()
{
    if (manager)
    {
        auto res = manager->read("log.ini");
        if (res.size()>2) return res.at(2);
    }

    return {};
}

/*!
Выполняет генерацию ini скрипта для ID_Info_Con.exe
*/
void IniDataProcessor::process()
{
    QString formatted;
    for (auto it = storage->begin(); it != storage->end() ; it++)
    {
        formatted.push_back("00000000\r\n");
        formatted.push_back(it->genericIniSize() + "\r\n");
        formatted.push_back(it->at(FILE_PATH).toString()+"\r\n");
        formatted.push_back(settings->loadpath + "/"+it->genericName()+"\r\n"+" "+"\r\n");
        formatted.push_back(it->at(DESCRIPTION).toString()+"\r\n");
        formatted.push_back(it->at(VERSION).toString().rightJustified(2,'0') + " " + it->at(REVISION).toString().rightJustified(2,'0') + "\r\n");
    }

    if (manager)
    {
        manager->setFilePath("conf.ini");
        manager->write(QStringList(formatted));
    }
}
