#include "batchiniinterpreter.h"

BatchIniInterpreter::BatchIniInterpreter(std::shared_ptr<Manager> &m1, std::shared_ptr<Manager> &m2)
{
    batchinterpreter = std::make_unique<BatchInterpreter>();
    iniinterpreter   = std::make_unique<IniDataInterpreter>();

    iniinterpreter->setFileManager(m1);
    batchinterpreter->setFileManager(m2);
}

BatchIniInterpreter::~BatchIniInterpreter()
{

}

void BatchIniInterpreter::read()
{
    iniinterpreter->read();
}

void BatchIniInterpreter::write(DataStorage* storage)
{
    if (storage)
    {
        iniinterpreter->write(storage);
        batchinterpreter->write(storage);
    }
}
