/*!
\file tblprocessor.h
\brief Заголовочный файл с описанием методов класса TblDataProcessor (формирует информацию о состоянии настроек программы и о данных, которые установил пользователь)
\authors Аркадий Сигов
Данный файл содержит в себе определения методов класса, используемых в программе
*/


#pragma once
#include "dataprocessor.h"

enum class TblMode
{
    write,
    read
};

class TblDataProcessor : public DataProcessor
{
public:
    TblDataProcessor(QObject* parent = nullptr) : DataProcessor(parent) {}
    ~TblDataProcessor() = default;
    void setMode(const QString&,const TblMode&);
    void process() override;
private:
    void writeTbl();
    void readTbl();
    TblMode  mode;
};
