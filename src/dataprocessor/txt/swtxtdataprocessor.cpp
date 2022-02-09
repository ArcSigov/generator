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
    for (auto it = s->begin(); it != s->end(); it++)
    {
        auto str = settings.abspath + "/" + it->genericName() + "\r\n";
        for (const auto& h: qAsConst(header[settings.type]))
        {
            formatted.push_back(h + " 0 " + str);
            formatted.push_back(h + ""+ it->genericType() +"" + str);
        }
    }

    if (m)
    {
        m->setFilePath(filename);
        m->write(formatted);
    }
}


/*!
Устанавливает настройки для сохранения выходного файла с наименованием файла в зависимости от выбранного блока
\param[in] &_settings ссылка на настройки программы
*/
void FlashSwTxtDataProcessor::setSettings(const Settings &_settings)
{
    settings = _settings;
    switch(settings.type)
    {
        case BlockType::bis:
            filename = settings.abspath+"/sw_load_bis.txt";
            break;
        case BlockType::bcvm:
            filename = settings.abspath+"/sw_load_bcvm.txt";
            break;
        case BlockType::bgs:
            filename = settings.abspath+"/sw_load_bgs.txt";
            break;
        case BlockType::undef:
        default:
        break;
    }
}
