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
#include "storage.h"
#include "messages.h"


class DataProcessor : public QObject
{
    Q_OBJECT
public:
    DataProcessor(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~DataProcessor()  = default;
    virtual void process() = 0;
    virtual void setFileManager(Manager* _manager) {manager = _manager;}
signals:
    void sendMessage(const MessageCategory& category = MessageCategory::notify,const QString& text = "");
protected:
    Manager* manager;
};
