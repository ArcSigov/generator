#include "generator.h"

Generator::Generator(QObject *parent) : QObject(parent),
    w(new MainWindow(&s))
{
    AbstractFileSystem*  f = new FileSystem(this);
    FileDataInterpreter* i = new TblFileInterpreter(&s,this);
    connect(w,&MainWindow::filePathSetted,f,&AbstractFileSystem::readFile);
    connect(f,&AbstractFileSystem::Result,i,&FileDataInterpreter::readFileData);
}

Generator::~Generator()
{
    delete w;
}

void Generator::run()
{
    w->show();
}
