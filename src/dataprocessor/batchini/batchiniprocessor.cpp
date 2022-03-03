#include "batchiniprocessor.h"

BatchIniProcessor::BatchIniProcessor(Manager* to_ini, Manager* to_batch) :
    iniprocessor(std::make_unique<IniDataProcessor>()),
    batchprocessor(std::make_unique<BatchIdInfoProcessor>())
{
    iniprocessor->setFileManager(to_ini);
    batchprocessor->setFileManager(to_batch);
}

/*!
Выполняет одновременную генерацию ini файла и генерацию batch скрипта для программы Id_Info_con.exe
*/
void BatchIniProcessor::process()
{
    iniprocessor->setMode(IniMode::write);
    iniprocessor->process();
    batchprocessor->process();
    iniprocessor->setMode(IniMode::read);
    iniprocessor->process();
}
