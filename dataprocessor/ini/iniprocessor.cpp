#include "iniprocessor.h"
#include "tablerowprop.h"


/*!
Читает результат выполнения программы ID_Info_Con.exe
\param[out] QString результат выполнения программы
*/
QString IniDataProcessor::quittance()
{
    if (m)
    {
        auto res = m->read("log.ini");
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
    for (auto it = s->begin(); it != s->end() ; it++)
    {
        formatted.push_back("00000000\r\n");
        formatted.push_back(it->genericSize() + "\r\n");
        formatted.push_back(it->at(FILE_PATH).toString()+"\r\n");
        formatted.push_back(output_directory + "/"+it->genericName()+"\r\n"+" "+"\r\n");
        formatted.push_back(it->at(DESCRIPTION).toString()+"\r\n");
        formatted.push_back(it->at(VERSION).toString().rightJustified(2,'0') + " " + it->at(REVISION).toString().rightJustified(2,'0') + "\r\n");
    }

    if (m)
    {
        m->setFilePath("conf.ini");
        m->write(QStringList(formatted));
    }
}

/*!
Устанавливает процессору ini файлов путь для помещения сгенерированного программой ID_Info_Con.exe файла
\param[in] &_settings ссылка на настройки программы
*/
void IniDataProcessor::setSettings(const Settings& _settings)
{
    output_directory = _settings.abspath;
}
