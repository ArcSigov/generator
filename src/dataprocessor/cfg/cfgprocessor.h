/*!
\file cfgprocessor.h
\brief Заголовочный файл с описанием методов и объектов класса CfgDataProcessor ( выполняет генерацию конфигурационного файла загрузки для ПЗУ)
\authors Аркадий Сигов
Данный файл содержит в себе определения методов класса, используемых при работе с объектом класса CfgDataProcessor
*/

#pragma once

#include "dataprocessor.h"
#include "blockcfg.h"

class CfgDataProcessor : public DataProcessor
{
public:
    CfgDataProcessor();
    ~CfgDataProcessor() = default;
    virtual void process() override;
private:
    std::unique_ptr<BlockCfg>                     block;
};
