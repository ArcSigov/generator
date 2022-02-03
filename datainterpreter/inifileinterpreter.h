#ifndef INIDATAINTERPRETER_H
#define INIDATAINTERPRETER_H

#include <QObject>
#include <QDebug>
#include "interpreter.h"
#include "datastorage.h"

class IniDataInterpreter : public FileDataInterpreter
{
public:
    explicit IniDataInterpreter();
    ~IniDataInterpreter() = default;
    virtual void read() override;
    virtual void write(const DataStorage &storage = DataStorage()) override;
};

#endif
