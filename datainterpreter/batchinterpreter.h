#ifndef BATCHDATAINTERPRETER_H
#define BATCHDATAINTERPRETER_H


#include <QDebug>
#include "interpreter.h"
#include "datastorage.h"

class BatchInterpreter : public FileDataInterpreter
{
public:
    explicit BatchInterpreter();
    ~BatchInterpreter();
    virtual void write(DataStorage* storage) override;
private:
    QString cur_id_path;
    QString result_path;
};

#endif
