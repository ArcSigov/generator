#include "generator.h"
#include <QDebug>
Generator::Generator(QObject *parent) : QObject(parent),
    window(new MainWindow(&s)),
    manager(new FileManager(this)),
    system(new WinSystemProxy(this))
{

    interpreter[TBL] = new TblDataInterpreter(&s,this);
    interpreter[INI] = new IniDataInterpreter(&s,this);
    interpreter[BUTCH] = new ButchInterpreter(&s,this);

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

    auto inilist = interpreter[INI]->interpreteToFileData();
    auto butchlist = interpreter[BUTCH]->interpreteToFileData();
    for (auto i = 0; i < s.size(); i++)
    {
        manager->setFilePath(QDir::currentPath()+"/conf.ini");
        manager->writeToFile(QStringList(inilist[i]));
        system->command(butchlist[i]);
        auto status = manager->readFile(QDir::currentPath()+"/log.ini");
        interpreter[INI]->readFileData(status);
    }
}

void Generator::readTblFile(const QString &path)
{
    if (path.isEmpty()) return;

    auto res = manager->readFile(path);
    interpreter[TBL]->readFileData(res);
    window->updateTable();
}

void Generator::saveTblFile(const QString &path)
{
    if (path.isEmpty()) return;

    manager->setFilePath(path);
    auto res = manager->writeToFile(interpreter[TBL]->interpreteToFileData());
    window->showSaveFileResult(res);
}
