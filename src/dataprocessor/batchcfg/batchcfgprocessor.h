/*!
\file batchiniprocessor.h
\brief Заголовочный файл с описанием методов класса BatchIniProcessor (макрокоманда, содержащая в себе BatchProcessor и IniProcessor)
\authors Аркадий Сигов
Данный файл содержит в себе определения методов класса, используемых в программе
*/

#pragma once


#include "cfgprocessor.h"
#include "batchprocessor.h"

class BatchCfgMotProcessor : public DataProcessor
{
public:
     BatchCfgMotProcessor(Manager*, Manager*);
    ~BatchCfgMotProcessor() = default;
    virtual void process() override;
private:
    std::unique_ptr<DataProcessor>   cfgprocessor;
    std::unique_ptr<DataProcessor>   batchcfgprocessor;
};
