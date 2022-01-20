#include "generator.h"

Generator::Generator(QObject *parent) : QObject(parent),
    w(new MainWindow(&s))
{
    FileReader*  reader = new TblFileReader(this);
    FileDataInterpreter* interpreter = new TblFileInterpreter(&s,this);
    connect(w,&MainWindow::filePathSetted,reader,&FileReader::readFile);
    connect(reader,&FileReader::Result,interpreter,&FileDataInterpreter::readFileData);
    connect(interpreter,&FileDataInterpreter::dataUpdated,w,&MainWindow::updateTable);
}

Generator::~Generator()
{
    delete w;
}

void Generator::run()
{
    w->show();
}
