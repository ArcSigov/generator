#ifndef CFGINTERPRETER_H
#define CFGINTERPRETER_H

#include "interpreter.h"
#include <QVector>
#include "datastorage.h"

class CfgDataInterpreter : public FileDataInterpreter
{
    Q_OBJECT
public:
    explicit CfgDataInterpreter(QObject* parent = nullptr);
    ~CfgDataInterpreter();
    virtual void read() override;
    virtual void write(DataStorage* storage = nullptr) override;
};

#endif
