#include "generator.h"
#include "batchmanager.h"
#include "tblprocessor.h"
#include "cfgprocessor.h"
#include "tablerowprop.h"
#include "batchiniprocessor.h"
#include "txtdataprocessor.h"
#include "mainwindow.h"
#include <QDebug>

Generator::Generator(QObject *parent) : QObject(parent),
    mainwindow(std::make_unique<MainWindow>(this))
{
    ///< Создание пула менеджеров для сохранения результатов программы, выполнения пакетных команд
    managers.emplace_back(std::make_unique<FileManager>());
    managers.emplace_back(std::make_unique<BatchManager>());

    ///< Создание пула процессов-обработчиков
    processors.emplace_back(std::make_unique<TblDataProcessor>());
    processors.emplace_back(std::make_unique<BatchIniProcessor>(managers[0].get(),managers[1].get()));
    processors.emplace_back(std::make_unique<CfgDataProcessor>());
    processors.emplace_back(std::make_unique<FlashSwTxtDataProcessor>());
    processors.emplace_back(std::make_unique<FlashRsTxtDataProcessor>());

    ///< Установка процессорам адреса хранилища данных и менеджеров
    for (auto& processor: processors)
    {
        processor->setSettings(&settings);
        processor->setStorage(&storage);
        processor->setFileManager(managers[0].get());
    }
    mainwindow->show();
}

/*!
Выполняет запуск процессов генерации исходного кода, загрузочных файлов, файлов конфигурации
\param[in] flag Разрешение работать
*/
void Generator::run()
{
    for (auto& processor : processors)
    {
        if(!dynamic_cast<TblDataProcessor*>(processor.get()))
        {
            processor->process();
            emit workStatus(processor->quittance());
        }
    }
}
/*!
Выполняет чтение файла с настройками и данными для работы
\param[in] &path ссылка на местоположение файла
*/
void Generator::readTblFile(const QString &path)
{
    for (auto& processor : processors)
    {
        auto tbl = dynamic_cast<TblDataProcessor*>(processor.get());
        if (tbl)
        {
            tbl->setMode(path,TblMode::read);
            tbl->process();
            static_cast<MainWindow*>(mainwindow.get())->update();
            break;
        }
    }
    update();
}
/*!
Выполняет сохранение файла с настройками и данными
\param[in] &path ссылка на место сохранения файла
*/
void Generator::saveTblFile(const QString &path)
{
    if (path.isEmpty()) return;

    for (auto& processor : processors)
    {
        auto tbl = dynamic_cast<TblDataProcessor*>(processor.get());
        if (tbl)
        {
            tbl->setMode(path,TblMode::write);
            tbl->process();
            static_cast<MainWindow*>(mainwindow.get())->notify("Файл: "+ path +" сохранён");
            break;
        }
    }
}
/*!
Выполняет обновление настроек генератора
*/
void Generator::update()
{
    calcRomAddr();
    for (auto& processor : processors)
        processor->update();
}

/*!
Выполняет расчет адресов ПЗУ для исполняемых файлов
*/
void Generator::calcRomAddr()
{
    size_t rom_addr = 0;
    switch (settings.type)
    {
    case BlockType::bis:
    case BlockType::bcvm:
        rom_addr = 0xb0200000;
        break;
    case BlockType::bgs:
        rom_addr = 0xbc200000;
        break;
    case BlockType::undef:
    default: return;
    }
    qDebug() << "calc";
    for (auto it = storage.begin(); it != storage.end(); it++)
    {
        it->setRomAddr(rom_addr);
        if (it->fileSize() < 0x40000)
        {
            rom_addr+=0x40000;
        }
        else
        {
            int _size = it->fileSize();
            while (_size > 0)
            {
                rom_addr+=0x40000;
                _size-=0x40000;
            }
        }
    }
}

QVector<DataStorage>* Generator::getStorage()
{
    return &storage;
}

Settings* Generator::getSettings()
{
    return &settings;
}
