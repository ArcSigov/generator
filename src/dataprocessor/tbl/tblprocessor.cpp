#include "tblprocessor.h"


/*!
Читает tbl файл и выставляет результат чтения файла
\param[out] QString результат чтения tbl файла
*/
void TblDataProcessor::writeTbl()
{
    QStringList data;
    data.push_back(outputfolder);
    data.push_back(blocktype);

    for (auto it = storage->begin(); it != storage->end() ; it++)
    {
        if (it != storage->begin()) data.push_back("\r\n");

        QString str = "TABLE_ROW:";
        for (auto i = 0 ; i < COLUMN_COUNT; i++)
            str += it->at(i).toString() + ";";

        data.push_back(str);
    }
    manager->write(data);
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

void TblDataProcessor::setMode(const QString& path,const TblMode &_mode)
{
    mode = _mode;
    if (manager)
        manager->setFilePath(path);
}


void TblDataProcessor::readTbl()
{
    auto tbldata = manager->read();
    for (const auto& it:tbldata)
    {
        if (it.contains("OUTPUT_FOLDER:"))
        {
            settings->abspath = it.section(":",1);
        }
        else if (it.contains("BLOCK_TYPE:"))
        {
            settings->type  = it.contains("BIS")   ?  BlockType::bis :
                              it.contains("BGS")   ?  BlockType::bgs :
                              it.contains("BCVM")  ?  BlockType::bcvm : BlockType::undef;
        }
        else if (it.contains("TABLE_ROW:"))
        {
            auto list = it.section(":",1).split(";");
            DataStorage d;
            for (auto i = 0 ; i < list.size(); i++)
                d.set(list.at(i),i);
            storage->push_back(d);
        }
    }
}

void TblDataProcessor::update()
{
    outputfolder = "OUTPUT_FOLDER:"+settings->abspath + "\r\n";
    switch (settings->type)
    {
    case BlockType::bis:
        blocktype = "BLOCK_TYPE:BIS\r\n";
        break;
    case BlockType::bcvm:
        blocktype = "BLOCK_TYPE:BCVM\r\n";
        break;
    case BlockType::bgs:
        blocktype = "BLOCK_TYPE:BGS\r\n";
        break;
    default:break;
    }
}
