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

/*!
Устанавливает процессору ini файлов путь для сохранения сгенерированного программой Id_Info_con.exe загрузочного образа
\param[in] &_settings ссылка на настройки программы
*/
void BatchCfgMotProcessor::update()
{
    cfgprocessor->update();
    batchcfgprocessor->update();
}

void BatchCfgMotProcessor::setSettings(Settings *_settings)
{
    cfgprocessor->setSettings(_settings);
    batchcfgprocessor->setSettings(_settings);
}

void BatchCfgMotProcessor::setStorage(QVector<DataStorage> *_storage)
{
    cfgprocessor->setStorage(_storage);
}
