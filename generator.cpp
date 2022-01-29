#include "generator.h"

Generator::Generator(QObject *parent) : QObject(parent),
    window(new MainWindow(&s)),
    manager(new FileManager(this)),
    tblinterpreter(new TblDataInterpreter(&s,this)),
    iniinterpreter(new IniDataInterpreter(&s,this))
{
    connect(window,&MainWindow::filePathSetted,this,&Generator::readTblFile);
    connect(window,&MainWindow::saveFilePath,this,&Generator::saveTblFile);
    connect(window,&MainWindow::generateActive,this,&Generator::run);
    window->show();
}

Generator::~Generator()
{
    delete window;
}

void Generator::run(bool flag)
{
    if (!flag) return;
    manager->setFilePath(QDir::currentPath()+"/out/conf.ini");

    auto res = iniinterpreter->interpreteToFileData();
    for (const auto &it : res)
    {
        manager->writeToFile(QStringList(it));
    }
}

void Generator::readTblFile(const QString &path)
{
    auto res = manager->readFile(path);
    tblinterpreter->readFileData(res);
    window->updateTable();
}

void Generator::saveTblFile(const QString &path)
{
    manager->setFilePath(path);
    auto res = manager->writeToFile(tblinterpreter->interpreteToFileData());
    window->showSaveFileResult(res);
}
