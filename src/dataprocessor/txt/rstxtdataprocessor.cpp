#include "txtdataprocessor.h"


/*!
Выполняет генерацию загрузочного файла для интерфейса RS в ПЗУ
*/
void FlashRsTxtDataProcessor::process()
{
    QStringList formatted;
    for (auto i = 0ull ; i < storage.size(); i++)
    {
        formatted.push_back(QString::number(i+1) + " \r\n");
    }

    if (manager)
    {
        manager->setFilePath(settings.romrstxtname);
        manager->write(formatted);
    }
}
