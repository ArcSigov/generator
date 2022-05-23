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
    BatchIniProcessor(Manager*, Manager*, QObject* parent = nullptr);
    ~BatchIniProcessor() = default;
    void process() override;
};
