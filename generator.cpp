#include "generator.h"

Generator::Generator(QObject *parent) : QObject(parent),
    window(new MainWindow(&s))
{
    FileReader*  reader = new TblFileReader(this);
    FileDataInterpreter* interpreter = new TblFileInterpreter(&s,this);
    connect(window,&MainWindow::filePathSetted,reader,&FileReader::readFile);
    connect(reader,&FileReader::Result,interpreter,&FileDataInterpreter::readFileData);
    connect(interpreter,&FileDataInterpreter::dataUpdated,window,&MainWindow::updateTable);
}

Generator::~Generator()
{
    delete window;
}

void Generator::run()
{
    window->show();
}
