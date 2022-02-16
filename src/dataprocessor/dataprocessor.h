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
#include "options.h"

class DataProcessor
{
    public:
    DataProcessor()  = default;
    virtual ~DataProcessor()  = default;
public:
    virtual QString quittance(){ return QString();}
    virtual void process() = 0;
    virtual void update() = 0;
    virtual void setFileManager(Manager* _manager) {manager = _manager;}
    virtual void setStorage(QVector<DataStorage>* _storage) {storage = _storage;}
    virtual void setSettings(Settings* _settings) {settings = _settings;}
protected:
    Manager* manager;
    QVector<DataStorage>* storage;
    Settings* settings;
};
