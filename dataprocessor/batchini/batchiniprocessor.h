#ifndef BATCHINIDATAINTERPRETER
#define BATCHINIDATAINTERPRETER


#include "iniprocessor.h"
#include "batchprocessor.h"
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
