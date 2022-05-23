#include "batchiniprocessor.h"

BatchIniProcessor::BatchIniProcessor(Manager* to_ini, Manager* to_batch , QObject* parent) :
    DataProcessor(parent)
{
    DataProcessor* ini = new IniDataProcessor(this);
    DataProcessor* batch = new BatchIdInfoProcessor(this);

    ini->setObjectName("IniDataProcessor");
    batch->setObjectName("BatchIdInfoProcessor");
    ini->setFileManager(to_ini);
    batch->setFileManager(to_batch);

    QObject::connect(ini,&DataProcessor::sendMessage,this,&DataProcessor::sendMessage);
    QObject::connect(batch,&DataProcessor::sendMessage,this,&DataProcessor::sendMessage);
}

/*!
Выполняет одновременную генерацию ini файла и генерацию batch скрипта для программы Id_Info_con.exe
*/
void BatchIniProcessor::process()
{
    IniDataProcessor* iniprocessor;
    BatchIdInfoProcessor* batchprocessor;
    for (auto it : this->children())
    {
        if (it->objectName() == "IniDataProcessor")
        {
            iniprocessor = dynamic_cast<IniDataProcessor*>(it);
        }
        else if (it->objectName() == "BatchIdInfoProcessor")
        {
            batchprocessor = dynamic_cast<BatchIdInfoProcessor*>(it);
        }
    }

    iniprocessor->setMode(IniMode::write);
    iniprocessor->process();
    batchprocessor->process();
    iniprocessor->setMode(IniMode::read);
    iniprocessor->process();
}
