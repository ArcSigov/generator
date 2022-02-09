/*!
\file batchiniprocessor.h
\brief Заголовочный файл с описанием методов класса BatchIniProcessor (макрокоманда, содержащая в себе BatchProcessor и IniProcessor)
\authors Аркадий Сигов
Данный файл содержит в себе определения методов класса, используемых в программе
*/

#pragma once


#include "iniprocessor.h"
#include "batchprocessor.h"

class BatchIniProcessor : public DataProcessor
{
public:
     BatchIniProcessor(Manager*, Manager*);
    ~BatchIniProcessor() = default;
    void process() override;
    void setSettings(const Settings&) override;
    QString quittance() override;
private:
    std::unique_ptr<DataProcessor>   iniprocessor;
    std::unique_ptr<DataProcessor>   batchprocessor;
    QVector<DataStorage> store;
};
