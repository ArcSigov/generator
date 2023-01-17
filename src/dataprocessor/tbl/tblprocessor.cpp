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
    data.push_back("BLOCK_TYPE:" + Storage::load()->cfg().BlockName() + "\r\n");

    for (auto it = Storage::load()->data().begin(); it != Storage::load()->data().end() ; it++)
    {
        if (it != Storage::load()->data().begin()) data.push_back("\r\n");

        QString str = "TABLE_ROW:";
        for (auto i = 1 ; i < COLUMN_COUNT; i++)
            str += it->at(i).toString() + ";";
        data.push_back(str);
    }
    if (manager->write(data))
         emit sendMessage(MessageCategory::notify,"Файл сохранён");
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
    auto tbldata = manager->read(nullptr);
    auto storage = Storage::load();
    storage->data().clear();
    for (const auto& it:tbldata)
    {
        if (it.contains("OUTPUT_FOLDER:"))
        {
            storage->options().loadpath = it.section(":",1);
        }
        else if (it.contains("KERNEL_FOLDER:"))
        {
            storage->options().kernelpath = it.section(":",1);
        }
        else if (it.contains("BLOCK_TYPE:"))
        {
            storage->cfg().setCurrentBlock(it.section(":",1));
        }
        else if (it.contains("SECTION_SIZE:"))
        {
            storage->options().max_rom_section_size   = it.section(":",1).toUInt(nullptr,16);
        }
        else if (it.contains("TABLE_ROW:"))
        {
            auto list = it.section(":",1).split(";");
            DataStorage d;
            for (auto i = 0 ; i < list.size(); i++)
                d.set(list.at(i),i+1);
            storage->data().push_back(d);
        }
    }

    if (storage->data().size())
    {
        emit sendMessage(MessageCategory::dataReady);
        storage->sort();
        storage->calcRom();
    }
}

