#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <QVector>
#include "manager.h"
#include "datastorage.h"
#include <memory>

class FileDataInterpreter
{
    public:
    explicit FileDataInterpreter(){};
    virtual ~FileDataInterpreter() {};
public:
    virtual void read(){};
    virtual void write(DataStorage* storage = nullptr) = 0;
    void setFileManager(std::shared_ptr<Manager>& _manager) {m = _manager;}
    std::shared_ptr<Manager>& manager() {return m;}
protected:
    std::shared_ptr<Manager> m;
};

#endif // INTERPRETER_H
