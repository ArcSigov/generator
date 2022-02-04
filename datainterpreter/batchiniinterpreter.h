#ifndef BATCHINIDATAINTERPRETER
#define BATCHINIDATAINTERPRETER


#include "inifileinterpreter.h"
#include "batchinterpreter.h"
#include "batchmanager.h"
#include "filemanager.h"


class BatchIniProcessor : public DataProcessor
{
public:
     BatchIniProcessor(Manager*, Manager*);
    ~BatchIniProcessor() = default;
    void process() override;
    QString quittance() override;
private:
    std::unique_ptr<DataProcessor>   iniprocessor;
    std::unique_ptr<DataProcessor>   batchprocessor;
    QVector<DataStorage> store;
};








#endif
