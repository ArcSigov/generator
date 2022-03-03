#include "txtdataprocessor.h"


/*!
Выполняет генерацию загрузочного файла для интерфейса SW в ПЗУ
*/
void FlashSwTxtDataProcessor::process()
{
    QStringList formatted;
    for (auto it = storage.begin(); it != storage.end(); it++)
    {
        auto str = QString::number(it->romAddr(),16) + " " + settings.loadpath + "/" + it->genericName() + "\r\n";
        for (auto i = 0 ; i < 2 ; i++)
        {
            formatted.push_back(settings.header[i] + " f " + str);
            formatted.push_back(settings.header[i] + " 0 " + str);
        }
    }
    formatted.push_back(settings.kernelflashstr);
    formatted.push_back(settings.cfgstr);
    if (manager)
    {
        manager->setFilePath(settings.romswtxtname);
        manager->write(formatted);
    }
}


/*!
Выполняет генерацию загрузочного файла для интерфейса SW в ОЗУ
*/
void RamSwTxtDataProcessor::process()
{
    QStringList formatted;
    auto counter = 1;
    for (auto it = storage.begin(); it != storage.end(); it++)
    {
        formatted.push_back(QString::number(counter++) +                        //module
                            " 1 " +                                             //always 1
                            QString::number(it->at(MODULE_NUM).toUInt(),16) +   //la
                            " a0040000 "+                                       //start ram addr always const
                            QString::number(!it->genericType()) +               // mot or elf
                            " " + QString::number(it->at(RAM_ADDR).toUInt(),16) +
                            " " +
                            it->at(FILE_PATH).toString() + "\r\n");             //abs path
    }
    if (manager)
    {
        manager->setFilePath(settings.ramswtxtname);
        manager->write(formatted);
    }
}

