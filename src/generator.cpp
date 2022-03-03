#include "generator.h"
#include "batchmanager.h"
#include "tblprocessor.h"
#include "tablerowprop.h"
#include "batchiniprocessor.h"
#include "batchcfgprocessor.h"
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
    processors.emplace_back(std::make_unique<BatchCfgMotProcessor>(managers[0].get(),managers[1].get()));
    processors.emplace_back(std::make_unique<FlashSwTxtDataProcessor>());
    processors.emplace_back(std::make_unique<FlashRsTxtDataProcessor>());
    processors.emplace_back(std::make_unique<RamSwTxtDataProcessor>());

    for (auto& processor: processors)
        processor->setFileManager(managers[0].get());

    mainwindow->show();
}

/*!
Выполняет запуск процессов генерации исходного кода, загрузочных файлов, файлов конфигурации
\param[in] flag Разрешение работать
*/
void Generator::run()
{
    Storage::load()->calcRom();
    for (auto& processor : processors)
    {
        if(!dynamic_cast<TblDataProcessor*>(processor.get()))
            processor->process();
    }
    static_cast<MainWindow*>(mainwindow.get())->update();
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
            storage.clear();
            tbl->setMode(path,TblMode::read);
            tbl->process();
            Storage::load()->sort();
            static_cast<MainWindow*>(mainwindow.get())->update();
            break;
        }
    }
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
