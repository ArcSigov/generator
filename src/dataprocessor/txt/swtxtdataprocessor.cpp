#include "txtdataprocessor.h"

FlashSwTxtDataProcessor::FlashSwTxtDataProcessor()
{
    header[BlockType::bis].push_back("1 1 25 a0040000 ");
    header[BlockType::bis].push_back("10 1 49 a0040000");

    header[BlockType::bcvm].push_back("1 1 25 a0040000");
    header[BlockType::bcvm].push_back("10 1 49 a0040000");

    header[BlockType::bgs].push_back("1 1 25 a0040000");
    header[BlockType::bgs].push_back("1 2 26 a0040000");
}

/*!
Выполняет генерацию загрузочного файла для интерфейса SW в ПЗУ
*/
void FlashSwTxtDataProcessor::process()
{
    QStringList formatted;
    for (auto it = storage->begin(); it != storage->end(); it++)
    {
        auto str = QString::number(it->romAddr(),16) + " " + settings->loadpath + "/" + it->genericName() + "\r\n";
        for (const auto& h: qAsConst(header[settings->type]))
        {
            formatted.push_back(h + " f " + str);
            formatted.push_back(h + " 0 " + str);
        }
    }

    if (manager)
    {
        manager->setFilePath(filename);
        manager->write(formatted);
    }
}


/*!
Устанавливает настройки для сохранения выходного файла с наименованием файла в зависимости от выбранного блока
\param[in] &_settings ссылка на настройки программы
*/
void FlashSwTxtDataProcessor::update()
{
    switch(settings->type)
    {
        case BlockType::bis:
            filename = settings->loadpath+"/sw_load_bis_rom.txt";
            break;
        case BlockType::bcvm:
            filename = settings->loadpath+"/sw_load_bcvm_rom.txt";
            break;
        case BlockType::bgs:
            filename = settings->loadpath+"/sw_load_bgs_rom.txt";
            break;
        case BlockType::undef:
        default:
        break;
    }
}

/*!
Выполняет генерацию загрузочного файла для интерфейса SW в ОЗУ
*/
void RamSwTxtDataProcessor::process()
{
    QStringList formatted;
    auto counter = 1;
    for (auto it = storage->begin(); it != storage->end(); it++)
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
        manager->setFilePath(filename);
        manager->write(formatted);
    }
}


/*!
Устанавливает настройки для сохранения выходного файла с наименованием файла в зависимости от выбранного блока
\param[in] &_settings ссылка на настройки программы
*/
void RamSwTxtDataProcessor::update()
{
    switch(settings->type)
    {
    case BlockType::bis:
        filename = settings->loadpath+"/sw_load_bis_ram.txt";
        break;
    case BlockType::bcvm:
        filename = settings->loadpath+"/sw_load_bcvm_ram.txt";
        break;
    case BlockType::bgs:
        filename = settings->loadpath+"/sw_load_bgs_ram.txt";
        break;
    case BlockType::undef:
    default:
        break;
    }
}
