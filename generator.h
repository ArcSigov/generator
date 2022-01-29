#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>
#include <QVector>
#include "datastorage.h"
#include "mainwindow.h"
#include "tblfilereader.h"
#include "tblfileinterpreter.h"

class Generator : public QObject
{
    Q_OBJECT
public:
    explicit Generator(QObject *parent = nullptr);
    ~Generator();
private:
    QVector<DataStorage> s;
    MainWindow* window;
    FileManager* manager;
    FileDataInterpreter* interpreter;
};

#endif // GENERATOR_H
