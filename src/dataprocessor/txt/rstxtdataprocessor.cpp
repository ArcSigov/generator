#include "txtdataprocessor.h"


/*!
Выполняет генерацию загрузочного файла для интерфейса RS в ПЗУ
*/
void FlashRsTxtDataProcessor::process()
{
    QStringList formatted;
    for (auto i = 0 ; i < storage->size(); i++)
    {
        formatted.push_back(QString::number(i+1) + " \r\n");
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
void FlashRsTxtDataProcessor::update()
{
    switch(settings->type)
    {
        case BlockType::bis:
        filename = settings->loadpath+"/rs_load_bis.txt";
            break;
        case BlockType::bcvm:
            filename = settings->loadpath+"/rs_load_bcvm.txt";
            break;
        case BlockType::bgs:
            filename = settings->loadpath+"/rs_load_bgs.txt";
            break;
        case BlockType::undef:
        default:
        break;
    }
}
