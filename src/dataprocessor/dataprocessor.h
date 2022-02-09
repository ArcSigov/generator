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
    virtual void setFileManager(Manager* _m) {m = _m;}
    virtual void setStorage(QVector<DataStorage>* _s) {s = _s;}
    virtual void setSettings(const Settings&) {}
    Manager* manager() {return m;}
protected:
    Manager* m;
    QVector<DataStorage>* s;
};
