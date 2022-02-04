#ifndef TBLDATAINTERPRETER_H
#define TBLDATAINTERPRETER_H


#include <QDebug>
#include "dataprocessor.h"

class TblDataProcessor : public DataProcessor
{
public:
     TblDataProcessor() = default;
    ~TblDataProcessor() = default;
    virtual QString quittance() override;
    virtual void process() override;
    virtual void lock(bool) override;
private:
    bool locked = false;
};

#endif
