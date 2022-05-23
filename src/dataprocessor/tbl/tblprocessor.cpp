#include "tblprocessor.h"


/*!
Читает tbl файл и выставляет результат чтения файла
\param[out] QString результат чтения tbl файла
*/
void TblDataProcessor::writeTbl()
{
    QStringList data;

    data.push_back("OUTPUT_FOLDER:"+Storage::load()->options().loadpath + "\r\n");
    data.push_back("KERNEL_FOLDER:"+Storage::load()->options().kernelpath + "\r\n");
    data.push_back("SECTION_SIZE:"+ QString::number(Storage::load()->options().max_rom_section_size,16)+ "\r\n");
    switch (Storage::load()->options().type)
    {
        case BlockType::bis:  data.push_back("BLOCK_TYPE:BIS\r\n");  break;
        case BlockType::bcvm: data.push_back("BLOCK_TYPE:BCVM\r\n"); break;
        case BlockType::bgs:  data.push_back("BLOCK_TYPE:BGS\r\n");  break;
        default:break;
    }

    for (auto it = Storage::load()->data().begin(); it != Storage::load()->data().end() ; it++)
    {
        if (it != Storage::load()->data().begin()) data.push_back("\r\n");

        QString str = "TABLE_ROW:";
        for (auto i = 1 ; i < COLUMN_COUNT; i++)
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
    if (manager)  manager->setFilePath(path);
}


void TblDataProcessor::readTbl()
{
    qDebug() << __PRETTY_FUNCTION__;
    auto tbldata = manager->read();
    for (const auto& it:tbldata)
    {
        if (it.contains("OUTPUT_FOLDER:"))
        {
            Storage::load()->options().loadpath = it.section(":",1);
        }
        else if (it.contains("KERNEL_FOLDER:"))
        {
            Storage::load()->options().kernelpath = it.section(":",1);
        }
        else if (it.contains("BLOCK_TYPE:"))
        {
            Storage::load()->options().type   = it.contains("BIS")   ?  BlockType::bis :
                              it.contains("BGS")   ?  BlockType::bgs :
                              it.contains("BCVM")  ?  BlockType::bcvm : BlockType::undef;
        }
        else if (it.contains("SECTION_SIZE:"))
        {
            Storage::load()->options().max_rom_section_size   = it.section(":",1).toUInt(nullptr,16);
        }
        else if (it.contains("TABLE_ROW:"))
        {
            auto list = it.section(":",1).split(";");
            DataStorage d;
            for (auto i = 0 ; i < list.size(); i++)
                d.set(list.at(i),i+1);
            Storage::load()->data().push_back(d);
        }
    }
}

