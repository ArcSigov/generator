#include "generator.h"
#include <QDebug>
Generator::Generator(QObject *parent) : QObject(parent),
    window(new MainWindow(&s))
{

    Manager* filemanager = new FileManager(this);
    Manager* batchmanager = new BatchManager(this);

    interpreter[TBL]   = new TblDataInterpreter(&s,this);
    interpreter[INI]   = new IniDataInterpreter(this);
    interpreter[BATCH] = new BatchInterpreter(this);
    interpreter[CFG]   = new CfgDataInterpreter(this);

    interpreter[TBL]->setFileManager(filemanager);
    interpreter[INI]->setFileManager(filemanager);
    interpreter[BATCH]->setFileManager(batchmanager);

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

    for (auto it = s.begin(); it != s.end(); it++)
    {
        for (auto _interpreter = interpreter.begin()+1; _interpreter != interpreter.end(); _interpreter++)
        {
            if (_interpreter != interpreter.begin()+1) interpreter[INI]->read();

            _interpreter.value()->write(it);
        }
    }
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
