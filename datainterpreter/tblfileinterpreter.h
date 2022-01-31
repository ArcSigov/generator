#ifndef TBLDATAINTERPRETER_H
#define TBLDATAINTERPRETER_H

#include <QObject>
#include <QDebug>
#include "interpreter.h"
#include "datastorage.h"

class TblDataInterpreter : public FileDataInterpreter
{
    Q_OBJECT
public:
    explicit TblDataInterpreter(QVector<DataStorage>* s = nullptr,QObject* parent = nullptr);
    ~TblDataInterpreter();
    virtual void read() override;
    virtual void write() override;
private:
    QVector<DataStorage>* v;
};

#endif
