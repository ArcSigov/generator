#ifndef INIDATAINTERPRETER_H
#define INIDATAINTERPRETER_H

#include <QObject>
#include <QDebug>
#include "interpreter.h"
#include "datastorage.h"

class IniDataInterpreter : public FileDataInterpreter
{
    Q_OBJECT
public:
    explicit IniDataInterpreter(QVector<DataStorage>* s = nullptr,QObject* parent = nullptr);
    ~IniDataInterpreter();
    virtual void read() override;
    virtual void write() override;
private:
    QVector<DataStorage>* v;
};

#endif
