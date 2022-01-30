#include "generator.h"
#include <QDebug>
Generator::Generator(QObject *parent) : QObject(parent),
    window(new MainWindow(&s)),
    manager(new FileManager(this)),
    tblinterpreter(new TblDataInterpreter(&s,this)),
    iniinterpreter(new IniDataInterpreter(&s,this)),
    system(new WinSystemProxy(this))
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

    auto res = iniinterpreter->interpreteToFileData();
    for (const auto &it : res)
    {
        manager->setFilePath(QDir::currentPath()+"/conf.ini");
        manager->writeToFile(QStringList(it));
        system->command("");
        auto status = manager->readFile(QDir::currentPath()+"/log.ini");
        iniinterpreter->readFileData(res);
    }
}

void Generator::readTblFile(const QString &path)
{
    if (path.isEmpty()) return;

    auto res = manager->readFile(path);
    tblinterpreter->readFileData(res);
    window->updateTable();
}

void Generator::saveTblFile(const QString &path)
{
    if (path.isEmpty()) return;

    manager->setFilePath(path);
    auto res = manager->writeToFile(tblinterpreter->interpreteToFileData());
    window->showSaveFileResult(res);
}
