/*!
\file generator.h
\brief Заголовочный файл с описанием методов класса Generator (основное ядро программы)
\authors Аркадий Сигов
Данный файл содержит в себе определения методов класса, используемых в программе
*/

#pragma once

#include <QObject>
#include <QMainWindow>
#include "datastorage.h"
#include "dataprocessor.h"
#include "filemanager.h"


class Generator : public QObject
{
    Q_OBJECT
    QVector<DataStorage> storage;
    Settings settings;
    std::unique_ptr<QMainWindow> mainwindow;
    std::vector<std::unique_ptr<DataProcessor>> processors;
    std::vector<std::unique_ptr<Manager>> managers;
public:
    explicit Generator(QObject *parent = nullptr);
    ~Generator() = default;
    void run();
    void readTblFile(const QString& path);
    void saveTblFile(const QString& path);
    void update();
    void sortStorage();
    QVector<DataStorage>* getStorage();
    Settings* getSettings();
signals:
    void workStatus(const QString& result);
    void settingsUpdated();
private:
    void calcRomAddr();
};
