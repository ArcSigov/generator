/*!
\file generator.h
\brief Заголовочный файл с описанием методов класса Generator (основное ядро программы)
\authors Аркадий Сигов
Данный файл содержит в себе определения методов класса, используемых в программе
*/

#pragma once

#include <QObject>
#include "datastorage.h"
#include "mainwindow.h"
#include "optionwindow.h"
#include "filemanager.h"
#include "batchmanager.h"
#include "tblprocessor.h"
#include "cfgprocessor.h"
#include "tablerowprop.h"
#include "batchiniprocessor.h"
#include "txtdataprocessor.h"

class Generator : public QObject
{
    Q_OBJECT
public:
    explicit Generator(QObject *parent = nullptr);
    ~Generator() = default;
signals:
    void workStatus(const QString& result);
    void settingsUpdated();
private:
    void run(bool);
    void readTblFile(const QString& path);
    void saveTblFile(const QString& path);
    void update();
    QVector<DataStorage> storage;
    Settings settings;
    std::unique_ptr<MainWindow> mainwindow;
    std::unique_ptr<OptionWindow> optionwindow;
    std::vector<std::unique_ptr<DataProcessor>> processors;
    std::vector<std::unique_ptr<Manager>> managers;
};
