#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>
#include <QVector>
#include <QDir>
#include "datastorage.h"
#include "mainwindow.h"
#include "optionwindow.h"
#include "filemanager.h"
#include "batchmanager.h"
#include "tblprocessor.h"
#include "cfgprocessor.h"
#include "tablerowprop.h"
#include "batchiniprocessor.h"


class Generator : public QObject
{
    Q_OBJECT
    enum {
        TBL,
        BATCHINI,
        CFG
    };
public:
    explicit Generator(QObject *parent = nullptr);
    ~Generator() = default;
signals:
    void workStatus(const QString& result);
private:
    void run(bool);
    void readTblFile(const QString& path);
    void saveTblFile(const QString& path);
    void updateSettings(const Settings &);
    QVector<DataStorage> s;
    std::unique_ptr<MainWindow> mainwindow;
    std::vector<std::unique_ptr<DataProcessor>> processors;
    std::vector<std::unique_ptr<Manager>> managers;
};

#endif // GENERATOR_H
