#ifndef BATCHINIDATAINTERPRETER
#define BATCHINIDATAINTERPRETER


#include "inifileinterpreter.h"
#include "batchinterpreter.h"
#include "batchmanager.h"
#include "filemanager.h"


class BatchIniInterpreter : public FileDataInterpreter
{
public:
    explicit BatchIniInterpreter(std::shared_ptr<Manager>& m1, std::shared_ptr<Manager>& m2);
    ~BatchIniInterpreter();
    void read() override;
    void write(DataStorage* storage) override;
private:
    std::unique_ptr<FileDataInterpreter>   iniinterpreter;
    std::unique_ptr<FileDataInterpreter>   batchinterpreter;
};








#endif
