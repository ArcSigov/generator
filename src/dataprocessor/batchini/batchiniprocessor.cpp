#include "batchiniprocessor.h"

BatchIniProcessor::BatchIniProcessor(Manager* to_ini, Manager* to_batch) :
    iniprocessor(std::make_unique<IniDataProcessor>()),
    batchprocessor(std::make_unique<BatchIdInfoProcessor>())
{
    store.resize(1);
    iniprocessor->setStorage(&store);
    batchprocessor->setStorage(&store);
    iniprocessor->setFileManager(to_ini);
    batchprocessor->setFileManager(to_batch);
}

/*!
Возвращает сформированную процессором ini файлов квитанцию о результататах генерации программой Id_Info_con.exe загрузочных образов для ПЗУ
*/
QString BatchIniProcessor::quittance()
{
    return iniprocessor->quittance();
}

/*!
Выполняет одновременную генерацию ini файла и генерацию batch скрипта для программы Id_Info_con.exe
*/
void BatchIniProcessor::process()
{
    for (auto it = storage->begin(); it != storage->end(); it++)
    {
        store[0] = *it;
        iniprocessor->process();
        batchprocessor->process();
    }
}

/*!
Устанавливает процессору ini файлов путь для сохранения сгенерированного программой Id_Info_con.exe загрузочного образа
\param[in] &_settings ссылка на настройки программы
*/
void BatchIniProcessor::update()
{
    iniprocessor->setSettings(settings);
}
