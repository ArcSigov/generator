#include "batchcfgprocessor.h"

BatchCfgMotProcessor::BatchCfgMotProcessor(Manager* to_cfg, Manager* to_batch) :
    cfgprocessor(std::make_unique<CfgDataProcessor>()),
    batchcfgprocessor(std::make_unique<BatchCfgProcessor>())
{
    cfgprocessor->setFileManager(to_cfg);
    batchcfgprocessor->setFileManager(to_batch);
}

/*!
Выполняет одновременную генерацию ini файла и генерацию batch скрипта для программы Id_Info_con.exe
*/
void BatchCfgMotProcessor::process()
{
    cfgprocessor->process();
    batchcfgprocessor->process();
}

