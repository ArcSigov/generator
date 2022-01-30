#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>
#include <QVector>
#include <QDir>
#include "datastorage.h"
#include "mainwindow.h"
#include "filereader.h"
#include "tblfileinterpreter.h"
#include "inifileinterpreter.h"
#include "tablerowprop.h"
#include "winsystemproxy.h"

class Generator : public QObject
{
    Q_OBJECT
public:
    explicit Generator(QObject *parent = nullptr);
    ~Generator();    
private:
    void run(bool);
    void readTblFile(const QString& path);
    void saveTblFile(const QString& path);
    QVector<DataStorage> s;
    MainWindow* window;
    FileManager* manager;
    FileDataInterpreter* tblinterpreter;
    FileDataInterpreter* iniinterpreter;
    FileDataInterpreter* cfginterpreter;
    AbstractSystemProxy* system;
};

#endif // GENERATOR_H
