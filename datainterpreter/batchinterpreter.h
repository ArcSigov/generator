#ifndef BATCHDATAINTERPRETER_H
#define BATCHDATAINTERPRETER_H


#include <QDebug>
#include "interpreter.h"
#include "datastorage.h"

class BatchProcessor : public DataProcessor
{
public:
    explicit BatchProcessor();
    ~BatchProcessor() = default;
    virtual void process() override;
private:
    QString cur_id_path;
    QString result_path;
};

#endif
