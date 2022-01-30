#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>
#include <QVector>
#include <QDir>
#include <QMap>
#include "datastorage.h"
#include "mainwindow.h"
#include "filereader.h"
#include "tblfileinterpreter.h"
#include "inifileinterpreter.h"
#include "tablerowprop.h"
#include "winsystemproxy.h"
#include "butchinterpreter.h"


class Generator : public QObject
{
    Q_OBJECT
    enum {
        TBL,
        INI,
        BUTCH
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
    FileManager* manager;
    QMap<size_t,FileDataInterpreter*> interpreter;
    AbstractSystemProxy* system;
};

#endif // GENERATOR_H
