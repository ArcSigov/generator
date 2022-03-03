/*!
\file iniprocessor.h
\brief Заголовочный файл с описанием методов класса IniDataProcessor (формирует информацию для генерации файлов в программе ID_Info_Con.exe)
\authors Аркадий Сигов
Данный файл содержит в себе определения методов класса, используемых в программе
*/


#pragma once

#include <QObject>
#include <QDebug>
#include "dataprocessor.h"
#include "datastorage.h"

enum class IniMode
{
    undef,
    write,
    read
};

class IniDataProcessor : public DataProcessor
{
public:
    IniDataProcessor() = default;
    ~IniDataProcessor() = default;
    void process() override;
    void setMode(const IniMode&);
private:
    IniMode mode{IniMode::undef};
    void read();
    void write();
};
