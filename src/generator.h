/*!
\file generator.h
\brief Заголовочный файл с описанием методов класса Generator (основное ядро программы)
\authors Аркадий Сигов
Данный файл содержит в себе определения методов класса, используемых в программе
*/

#pragma once

#include <QObject>
#include "datastorage.h"
#include "dataprocessor.h"
#include <unordered_map>

class Generator : public QObject
{
    Q_OBJECT
    std::unordered_map<DataProcessor*,bool*> processors;
    std::vector<Manager*>       managers;
public:
    explicit Generator(QObject *parent = nullptr);
    ~Generator() = default;
    void run();
    void readTblFile(const QString&);
    void saveTblFile(const QString&);
    void runVerify(const QString&);
signals:
    void tblSaveStatus(const QString& result);
    void workCompleted();
    void sendMessage(const MessageCategory& category = MessageCategory::notify,const QString& text = "");
};
