#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>
#include <QVector>
#include "datastorage.h"
#include "mainwindow.h"
#include "abstractfilesystem.h"
#include "tblfileinterpreter.h"

class Generator : public QObject
{

    Q_OBJECT
public:
    explicit Generator(QObject *parent = nullptr);
    ~Generator();
    void run();
signals:

private:
    QVector<DataStorage> s;
    MainWindow* w;
};

#endif // GENERATOR_H
