/*!
\file cfgprocessor.h
\brief Заголовочный файл с описанием методов и объектов класса CfgDataProcessor ( выполняет генерацию конфигурационного файла загрузки для ПЗУ)
\authors Аркадий Сигов
Данный файл содержит в себе определения методов класса, используемых при работе с объектом класса CfgDataProcessor
*/

#pragma once

#include "dataprocessor.h"

class CfgDataProcessor : public DataProcessor
{
QString file_header ="\t\t\t\t\t/*WARNING !!! -> THIS FILE IS GENERATED AUTOMATICALLY. DO NOT EDIT THIS FILE MANUALLY <- WARNING !!!*/\r\n\r\n \
typedef struct{\r\n\
    unsigned short GA;\r\n\
    unsigned short LA;\r\n\
    unsigned long kernel_addr_rom;\r\n\
    unsigned long kernel_addr_ram;\r\n\
    unsigned long kernel_size;\r\n\
    unsigned long config_addr_rom;\r\n\
    unsigned long config_addr_ram;\r\n\
    unsigned long config_size;\r\n\
    unsigned long part1_addr_rom;\r\n\
    unsigned long part1_addr_ram;\r\n\
    unsigned long part1_size;\r\n\
    unsigned long part2_addr_rom;\r\n\
    unsigned long part2_addr_ram;\r\n\
    unsigned long part2_size;\r\n\
    unsigned long part3_addr_rom;\r\n\
    unsigned long part3_addr_ram;\r\n\
    unsigned long part3_size;\r\n\
}SoftLoad;\r\n\r\n\r\n\
const SoftLoad conf_info[]  =\r\n\
{\r\n\t\
/*module           --------  kernel ---------------    ---------- config --------------    ------------ app 1 -------------    ------------ app 2 -------------    ------------ app 3 ------------- */\r\n";
public:
    CfgDataProcessor(QObject* parent = nullptr) : DataProcessor(parent) {};
    ~CfgDataProcessor() = default;
    virtual void process() override;
};
