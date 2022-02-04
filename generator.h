#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>
#include <QVector>
#include <QDir>
#include "datastorage.h"
#include "mainwindow.h"
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
    ~Generator();    
private:
    void run(bool);
    void readTblFile(const QString& path);
    void saveTblFile(const QString& path);
    QVector<DataStorage> s;
    MainWindow* window;
    std::vector<std::unique_ptr<DataProcessor>> processors;
    std::vector<std::unique_ptr<Manager>> managers;
};

#endif // GENERATOR_H
