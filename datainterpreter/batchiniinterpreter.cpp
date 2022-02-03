#include "batchiniinterpreter.h"

BatchIniInterpreter::BatchIniInterpreter(std::shared_ptr<Manager> &m1, std::shared_ptr<Manager> &m2) :
    iniinterpreter(std::make_unique<IniDataInterpreter>()),
    batchinterpreter(std::make_unique<BatchInterpreter>())
{
    iniinterpreter->setFileManager(m1);
    batchinterpreter->setFileManager(m2);
}

void BatchIniInterpreter::read()
{
    iniinterpreter->read();
}

void BatchIniInterpreter::write(const DataStorage& storage)
{
    iniinterpreter->write(storage);
    batchinterpreter->write(storage);
}
