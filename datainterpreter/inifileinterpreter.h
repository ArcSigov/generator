#ifndef INIDATAINTERPRETER_H
#define INIDATAINTERPRETER_H

#include <QObject>
#include <QDebug>
#include "interpreter.h"
#include "datastorage.h"

class IniDataProcessor : public DataProcessor
{
public:
    IniDataProcessor() = default;
    ~IniDataProcessor() = default;
    virtual void process() override;
    virtual QString quittance() override;
};

#endif
