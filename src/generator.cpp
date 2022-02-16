#include "generator.h"
#include <QDebug>

Generator::Generator(QObject *parent) : QObject(parent),
    mainwindow(std::make_unique<MainWindow>(&storage)),
    optionwindow(std::make_unique<OptionWindow>(&settings))
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

    connect(mainwindow.get(),&MainWindow::filePathSetted, this,&Generator::readTblFile);                       ///< Соединенение главного окна с генератором с уведомлением о выборе файла для чтения
    connect(mainwindow.get(),&MainWindow::saveFilePath,   this,&Generator::saveTblFile);                       ///< Соединенение главного окна с генератором с уведомлением о выборе файла для записи
    connect(mainwindow.get(),&MainWindow::generateActive, this,&Generator::run);                               ///< Соединенение главного окна с генератором с уведомлением о начале работы
    connect(mainwindow.get(),&MainWindow::settingsClicked, optionwindow.get(),&OptionWindow::show);            ///< Соединенение главного окна с генератором с уведомлением о начале работы
    connect(optionwindow.get(),&OptionWindow::settingsUpdated,this,&Generator::update);                        ///< Соединенение главного окна с генератором с уведомлением о изменении пользовательских настроек
//    connect(mainwindow.get(),&MainWindow::clo,optionwindow.get(),&OptionWindow::close);
    mainwindow->show();
}

/*!
Выполняет запуск процессов генерации исходного кода, загрузочных файлов, файлов конфигурации
\param[in] flag Разрешение работать
*/
void Generator::run(bool flag)
{
    if (!flag) return;

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
            optionwindow->setSettings();
            mainwindow->updateTable();
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
    for (auto& processor : processors)
    {
        auto tbl = dynamic_cast<TblDataProcessor*>(processor.get());
        if (tbl)
        {
            tbl->setMode(path,TblMode::write);
            tbl->process();
            mainwindow->notify("Файл: "+ path +" сохранён");
            break;
        }
    }
}
/*!
Выполняет обновление процессов обработки
*/
void Generator::update()
{
    for (auto& processor : processors)
        processor->update();
}
