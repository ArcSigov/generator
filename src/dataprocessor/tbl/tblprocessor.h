/*!
\file tblprocessor.h
\brief Заголовочный файл с описанием методов класса TblDataProcessor (формирует информацию о состоянии настроек программы и о данных, которые установил пользователь)
\authors Аркадий Сигов
Данный файл содержит в себе определения методов класса, используемых в программе
*/


#pragma once
#include <QDebug>
#include "dataprocessor.h"

class TblDataProcessor : public DataProcessor
{
public:
     TblDataProcessor() = default;
    ~TblDataProcessor() = default;
    virtual QString quittance() override;
    virtual void process() override;
private:
    Settings settings;
};
