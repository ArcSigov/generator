#include "iniprocessor.h"
#include "tablerowprop.h"




/*!
Выполняет генерацию ini скрипта для ID_Info_Con.exe
*/
void IniDataProcessor::process()
{
    switch (mode)
    {
        case IniMode::read:  read();  break;
        case IniMode::write: write(); break;
        case IniMode::undef:
        default:return;
    }
}

void IniDataProcessor::read()
{
    for (auto it = Storage::load()->data().begin(); it != Storage::load()->data().end(); it++)
    {
        if(!it->at(IS_CHECKED).toBool())
            continue;

        if (manager)
        {
            auto res = manager->read(nullptr,it->genericName().replace('.','_')+"_log.ini");
            if (res.size()>8)
            {
                it->set(res.at(8).section(':',1).toUInt(nullptr,16),CRC);
                emit sendMessage(MessageCategory::warning,"Процесс генерации " + it->genericName() + " завершён без ошибок");
            }
        }
    }
}

void IniDataProcessor::write()
{

    for (auto it = Storage::load()->data().begin(); it != Storage::load()->data().end(); it++)
    {
        if(!it->at(IS_CHECKED).toBool())
            continue;

        QString formatted;
        formatted.push_back("00000000\r\n");
        formatted.push_back(it->genericIniSize() + "\r\n");
        formatted.push_back(it->at(FILE_PATH).toString()+"\r\n");
        formatted.push_back(Storage::load()->options().loadpath + "/"+it->genericName()+"\r\n"+" "+"\r\n");
        formatted.push_back(it->at(DESCRIPTION).toString()+"\r\n");
        formatted.push_back(it->at(VERSION).toString().rightJustified(2,'0') + " " + it->at(REVISION).toString().rightJustified(2,'0') + "\r\n");
        if (manager)
        {
            manager->setFilePath(it->genericName().replace('.','_')+".ini");
            manager->write(QStringList(formatted));
        }
    }
}

void IniDataProcessor::setMode(const IniMode &_mode)
{
    mode = _mode;
}
