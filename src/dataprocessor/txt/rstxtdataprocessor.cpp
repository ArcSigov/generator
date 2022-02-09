#include "txtdataprocessor.h"


/*!
Выполняет генерацию загрузочного файла для интерфейса RS в ПЗУ
*/
void FlashRsTxtDataProcessor::process()
{
    QStringList formatted;
    for (auto i = 0 ; i < s->size(); i++)
    {
        formatted.push_back(QString::number(i+1) + " \r\n");
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
void FlashRsTxtDataProcessor::setSettings(const Settings &_settings)
{
    switch(_settings.type)
    {
        case BlockType::bis:
            filename = _settings.abspath+"/rs_load_bis.txt";
            break;
        case BlockType::bcvm:
            filename = _settings.abspath+"/rs_load_bcvm.txt";
            break;
        case BlockType::bgs:
            filename = _settings.abspath+"/rs_load_bgs.txt";
            break;
        case BlockType::undef:
        default:
        break;
    }
}
