#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <QVector>
#include "manager.h"
#include "datastorage.h"
#include <memory>

class FileDataInterpreter
{
    public:
    FileDataInterpreter()  = default;
    virtual ~FileDataInterpreter()  = default;
public:
    virtual void read(){};
    virtual void write(const DataStorage& storage = DataStorage()) = 0;
    virtual void done(){};
    void setFileManager(std::shared_ptr<Manager>& _manager) {m = _manager;}
    Manager& manager() {return *m;}
protected:
    std::shared_ptr<Manager> m;
};

#endif // INTERPRETER_H
