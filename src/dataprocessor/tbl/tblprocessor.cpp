#include "tblprocessor.h"


/*!
Читает tbl файл и выставляет результат чтения файла
\param[out] QString результат чтения tbl файла
*/
QString TblDataProcessor::quittance()
{
    if (!locked)
    {
        auto tbldata = m->read();
        for (const auto& it:tbldata)
        {
            auto list = it.split(";");
            DataStorage d;
            for (auto i = 0 ; i < list.size(); i++)
                d.set(list.at(i),i);
            s->push_back(d);
        }
    }
    return QString();
}

/*!
Выполняет генерацию tbl файла для сохранения конфигурации и данных таблицы программы
*/
void TblDataProcessor::process()
{
    if (locked) return;

    QStringList data;
    for (auto it = s->begin(); it != s->end() ; it++)
    {
        if (it != s->begin()) data.push_back("\r\n");

        QString str;
        for (auto i = 0 ; i < COLUMN_COUNT; i++)
        {
            str += it->at(i).toString() + ";";
        }
        data.push_back(str);
    }
    m->write(data);
}

/*!
Устанавливает процессору tbl файлов признак запрета на выполнение работы
\param[in] _locked флаг установки запрета на работу процессора
*/
void TblDataProcessor::lock(bool _locked)
{
    locked = _locked;
}
