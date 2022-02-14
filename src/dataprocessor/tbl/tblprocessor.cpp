#include "tblprocessor.h"


/*!
Читает tbl файл и выставляет результат чтения файла
\param[out] QString результат чтения tbl файла
*/
void TblDataProcessor::writeTbl()
{
    QStringList data;
    data.push_back(outputfolder+"\r\n");
    data.push_back(blocktype+"\r\n");

    for (auto it = s->begin(); it != s->end() ; it++)
    {
        if (it != s->begin()) data.push_back("\r\n");

        QString str;
        for (auto i = 0 ; i < COLUMN_COUNT; i++)
            str += it->at(i).toString() + ";";

        data.push_back(str);
    }
    m->write(data);
}

/*!
Выполняет генерацию tbl файла для сохранения конфигурации и данных таблицы программы
*/
void TblDataProcessor::process()
{
    switch (mode)
    {
        case (TblMode::read):  readTbl();  break;
        case (TblMode::write): writeTbl(); break;
        default: break;
    }
}

void TblDataProcessor::setMode(const TblMode &_mode)
{
    mode = _mode;
}

Settings TblDataProcessor::getSettings()
{
    return settings;
}

void TblDataProcessor::readTbl()
{
    auto tbldata = m->read();
    for (const auto& it:tbldata)
    {
        if (it.contains("OUTPUT_FOLDER:"))
        {
            settings.abspath = it.section(":",1);
        }
        else if (it.contains("BLOCK_TYPE:"))
        {
            settings.type  = it.contains("BIS")   ?  BlockType::bis :
                             it.contains("BGS")   ?  BlockType::bgs :
                             it.contains("BCVM")  ?  BlockType::bcvm : BlockType::undef;
        }
        else
        {
            auto list = it.split(";");
            DataStorage d;
            for (auto i = 0 ; i < list.size(); i++)
                d.set(list.at(i),i);
            s->push_back(d);
        }
    }
}
void TblDataProcessor::setSettings(const Settings &_settings)
{
    outputfolder = _settings.abspath;
    switch (settings.type)
    {
    case BlockType::bis:
        blocktype = "BLOCK:BIS\r\n";
        break;
    case BlockType::bcvm:
        blocktype = "BLOCK:BCVM\r\n";
        break;
    case BlockType::bgs:
        blocktype = "BLOCK:BGS\r\n";
        break;
    default:break;
    }
}
