#include "generator.h"
#include <QDebug>

Generator::Generator(QObject *parent) : QObject(parent),
    mainwindow(std::make_unique<MainWindow>(&s))
{

    managers.emplace_back(std::make_unique<FileManager>());
    managers.emplace_back(std::make_unique<BatchManager>());

    processors.emplace_back(std::make_unique<TblDataProcessor>());
    processors.emplace_back(std::make_unique<BatchIniProcessor>(managers[0].get(),managers[1].get()));
    processors.emplace_back(std::make_unique<CfgDataProcessor>());

    for (auto& it: processors)
    {
        it->setStorage(&s);
        it->setFileManager(managers[0].get());
    }

    connect(mainwindow.get(),&MainWindow::filePathSetted, this,&Generator::readTblFile);
    connect(mainwindow.get(),&MainWindow::saveFilePath,   this,&Generator::saveTblFile);
    connect(mainwindow.get(),&MainWindow::generateActive, this,&Generator::run);
    connect(mainwindow.get(),&MainWindow::settingsUpdated,this,&Generator::updateSettings);
    mainwindow->show();
}

void Generator::run(bool flag)
{
    if (!flag) return;

    processors[TBL]->lock(true);
    for (auto& processor : processors)
    {
        processor->process();
        emit workStatus(processor->quittance());
    }
    processors[TBL]->lock(false);
}


void Generator::readTblFile(const QString &path)
{
    processors[TBL]->manager()->setFilePath(path);
    processors[TBL]->quittance();
    mainwindow->updateTable();
}

void Generator::saveTblFile(const QString &path)
{
    processors[TBL]->manager()->setFilePath(path);
    processors[TBL]->process();
    mainwindow->showSaveFileResult(true);
}

void Generator::updateSettings(const Settings& _settings)
{
    for (auto& processor: processors)
        processor->setSettings(_settings);
}
