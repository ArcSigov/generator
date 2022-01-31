#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>
#include <QVector>
#include <QDir>
#include <QMap>
#include "datastorage.h"
#include "mainwindow.h"
#include "filemanager.h"
#include "batchmanager.h"
#include "tblfileinterpreter.h"
#include "inifileinterpreter.h"
#include "cfginterpreter.h"
#include "tablerowprop.h"
#include "batchinterpreter.h"


class Generator : public QObject
{
    Q_OBJECT
    enum {
        TBL,
        INI,
        BUTCH,
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
    QMap<size_t,FileDataInterpreter*> interpreter;
};

#endif // GENERATOR_H
