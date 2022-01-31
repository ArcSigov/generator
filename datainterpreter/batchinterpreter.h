#ifndef BATCHDATAINTERPRETER_H
#define BATCHDATAINTERPRETER_H

#include <QObject>
#include <QDebug>
#include "interpreter.h"
#include "datastorage.h"

class BatchInterpreter : public FileDataInterpreter
{
    Q_OBJECT
public:
    explicit BatchInterpreter(QVector<DataStorage> *s = nullptr, QObject* parent = nullptr);
    ~BatchInterpreter();
    virtual void read() override;
    virtual void write() override;
private:
    QVector<DataStorage> *v;
};

#endif
