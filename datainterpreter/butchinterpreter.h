#ifndef BUTCHDATAINTERPRETER_H
#define BUTCHDATAINTERPRETER_H

#include <QObject>
#include <QDebug>
#include "interpreter.h"
#include "datastorage.h"

class ButchInterpreter : public FileDataInterpreter
{
    Q_OBJECT
public:
    explicit ButchInterpreter(QVector<DataStorage> *s = nullptr, QObject* parent = nullptr);
    ~ButchInterpreter();
    virtual void read() override;
    virtual void write() override;
private:
    QVector<DataStorage> *v;
};

#endif