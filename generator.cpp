#include "generator.h"
#include <QDebug>
Generator::Generator(QObject *parent) : QObject(parent),
    window(new MainWindow(&s))
{

    Manager* filemanager = new FileManager(this);

    interpreter[TBL] = new TblDataInterpreter(&s,this);
    interpreter[INI] = new IniDataInterpreter(&s,this);
    interpreter[BUTCH] = new ButchInterpreter(&s,this);

    interpreter[TBL]->setFileManager(filemanager);
    interpreter[INI]->setFileManager(filemanager);
    interpreter[BUTCH]->setFileManager(new ButchManager(this));

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

    for (auto i = interpreter.begin()+1; i != interpreter.end(); i++)
        i.value()->write();
}

void Generator::readTblFile(const QString &path)
{
    if (path.isEmpty()) return;

    interpreter[TBL]->manager()->setFilePath(path);
    interpreter[TBL]->read();
    window->updateTable();
}

void Generator::saveTblFile(const QString &path)
{
    if (path.isEmpty()) return;

    interpreter[TBL]->manager()->setFilePath(path);
    interpreter[TBL]->write();
    window->showSaveFileResult(true);
}
