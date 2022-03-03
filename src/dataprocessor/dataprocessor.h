/*!
\file dataprocessor.h
\brief Заголовочный файл с описанием интерфейсов абстрактного класса DataProcessor
\authors Аркадий Сигов
Данный файл содержит в себе определения методов класса, используемых при работе с интерфейсом класса DataProcessor
*/

#pragma once

#include <QVector>
#include <QDebug>
#include "manager.h"
#include "datastorage.h"

class DataProcessor
{
public:
    DataProcessor()  = default;
    virtual ~DataProcessor()  = default;
    virtual void process() = 0;
    virtual void setFileManager(Manager* _manager) {manager = _manager;}
protected:
    Manager* manager;
    std::vector<DataStorage>& storage {Storage::load()->data()};
    Settings& settings                {Storage::load()->settings()};
};
