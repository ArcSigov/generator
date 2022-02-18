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
            filename = settings->loadpath+"/sw_load_bis.txt";
            break;
        case BlockType::bcvm:
            filename = settings->loadpath+"/sw_load_bcvm.txt";
            break;
        case BlockType::bgs:
            filename = settings->loadpath+"/sw_load_bgs.txt";
            break;
        case BlockType::undef:
        default:
        break;
    }
}
