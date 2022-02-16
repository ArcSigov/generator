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
    FlashSwTxtDataProcessor();
    ~FlashSwTxtDataProcessor() = default;
    virtual void process() override;
    virtual void update() override;
private:
    QString  filename;
    std::unordered_map<BlockType,QStringList> header;
};

class FlashRsTxtDataProcessor : public DataProcessor
{
public:
    FlashRsTxtDataProcessor()  = default;
    ~FlashRsTxtDataProcessor() = default;
    virtual void process() override;
    virtual void update() override;
private:
    //QString  cfg_rom_addr;
    QString  filename;
};
