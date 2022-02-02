#include "inifileinterpreter.h"
#include "tablerowprop.h"

IniDataInterpreter::IniDataInterpreter()
{

}

IniDataInterpreter::~IniDataInterpreter()
{

}

void IniDataInterpreter::read()
{
    auto log = m->read("log.ini");
    //emit status(log.at(2));
}

void IniDataInterpreter::write(DataStorage* storage)
{
    if(!storage) return;

    m->setFilePath("conf.ini");

    QString formatted;
    formatted.push_back("00000000\r\n");
    formatted.push_back(storage->genericSize() + "\r\n");
    formatted.push_back(storage->at(FILE_PATH).toString()+"\r\n");
    formatted.push_back(storage->genericName()+"\r\n"+" "+"\r\n");
    formatted.push_back(storage->at(DESCRIPTION).toString()+"\r\n");
    formatted.push_back(storage->at(VERSION).toString().rightJustified(2,'0') + " " + storage->at(REVISION).toString().rightJustified(2,'0') + "\r\n");
    m->write(QStringList(formatted));
}
