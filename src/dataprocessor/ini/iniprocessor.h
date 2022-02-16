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

class IniDataProcessor : public DataProcessor
{
public:
    IniDataProcessor() = default;
    ~IniDataProcessor() = default;
    virtual void process() override;
    virtual void update() override {};
    virtual QString quittance() override;
private:
    QString output_directory;
};
