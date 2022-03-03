/*!
\file txtdataprocessor.h
\brief Заголовочный файл с описанием методов класса SwTxtDataProcessor и RsTxtDataProcessor (формирует информацию дял загрузки образов через интерфейсы RS232, SW)
\authors Аркадий Сигов
Данный файл содержит в себе определения методов класса, используемых в программе
*/


#pragma once

#include "dataprocessor.h"
#include <unordered_map>

class FlashSwTxtDataProcessor : public DataProcessor
{
public:
    FlashSwTxtDataProcessor() = default;
    ~FlashSwTxtDataProcessor() = default;
    void process() override;
};

class RamSwTxtDataProcessor : public DataProcessor
{
public:
    RamSwTxtDataProcessor() = default;
    ~RamSwTxtDataProcessor() = default;
    void process() override;
};

class FlashRsTxtDataProcessor :  public DataProcessor
{
public:
    FlashRsTxtDataProcessor()  = default;
    ~FlashRsTxtDataProcessor() = default;
    void process() override;
};
