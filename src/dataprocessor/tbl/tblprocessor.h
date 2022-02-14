/*!
\file tblprocessor.h
\brief Заголовочный файл с описанием методов класса TblDataProcessor (формирует информацию о состоянии настроек программы и о данных, которые установил пользователь)
\authors Аркадий Сигов
Данный файл содержит в себе определения методов класса, используемых в программе
*/


#pragma once
#include <QDebug>
#include "dataprocessor.h"

enum class TblMode
{
    write,
    read
};

class TblDataProcessor : public DataProcessor
{
public:
     TblDataProcessor() = default;
    ~TblDataProcessor() = default;
    void         setMode(const TblMode&);
    Settings     getSettings();
    virtual void process() override;
    virtual void setSettings(const Settings&) override;
private:
    void writeTbl();
    void readTbl();
    Settings settings;
    TblMode  mode;
    QString outputfolder;
    QString blocktype;
};
