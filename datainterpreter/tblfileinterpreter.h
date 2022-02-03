#ifndef TBLDATAINTERPRETER_H
#define TBLDATAINTERPRETER_H


#include <QDebug>
#include "interpreter.h"
#include "datastorage.h"

class TblDataInterpreter : public FileDataInterpreter
{
public:
    explicit TblDataInterpreter(QVector<DataStorage>* s = nullptr);
    ~TblDataInterpreter() = default;
    virtual void read() override;
    virtual void write(const DataStorage &storage = DataStorage()) override;
private:
    QVector<DataStorage>* v;
};

#endif
