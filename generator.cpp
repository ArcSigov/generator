#include "generator.h"
#include <QDebug>

Generator::Generator(QObject *parent) : QObject(parent),
    window(new MainWindow(&s))
{

    managers.emplace_back(std::make_shared<FileManager>());
    managers.emplace_back(std::make_shared<BatchManager>());

    interpreter.emplace_back(std::make_unique<TblDataInterpreter>(&s));
    interpreter.emplace_back(std::make_unique<BatchIniInterpreter>(managers[0],managers[1]));
    interpreter.emplace_back(std::make_unique<CfgDataInterpreter>(BlockType::undef));

    interpreter[TBL]->setFileManager(managers[0]);

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

    for (const auto& data : qAsConst(s))
    {
        interpreter[BATCHINI]->read();
        for (auto i = 1ull ; i < interpreter.size(); i++){
            interpreter[i]->write(data);
        }
    }

    for (auto& _interpreter : interpreter)
        _interpreter->done();
}

void Generator::readTblFile(const QString &path)
{
    if (path.isEmpty()) return;

    interpreter[TBL]->manager().setFilePath(path);
    interpreter[TBL]->read();
    window->updateTable();
}

void Generator::saveTblFile(const QString &path)
{
    if (path.isEmpty()) return;

    interpreter[TBL]->manager().setFilePath(path);

    for (const auto& data : qAsConst(s))
        interpreter[TBL]->write(data);

    interpreter[TBL]->done();
    window->showSaveFileResult(true);
}
