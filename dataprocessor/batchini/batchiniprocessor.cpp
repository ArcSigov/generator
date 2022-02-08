#include "batchiniprocessor.h"

BatchIniProcessor::BatchIniProcessor(Manager* to_ini, Manager* to_batch) :
    iniprocessor(std::make_unique<IniDataProcessor>()),
    batchprocessor(std::make_unique<BatchProcessor>())
{
    store.resize(1);
    iniprocessor->setStorage(&store);
    batchprocessor->setStorage(&store);
    iniprocessor->setFileManager(to_ini);
    batchprocessor->setFileManager(to_batch);
}


QString BatchIniProcessor::quittance()
{
    return iniprocessor->quittance();
}

void BatchIniProcessor::process()
{
    for (auto it = s->begin(); it != s->end(); it++)
    {
        store[0] = *it;
        iniprocessor->process();
        batchprocessor->process();
    }
}

void BatchIniProcessor::setSettings(const Settings& _settings)
{
    iniprocessor->setSettings(_settings);
}
