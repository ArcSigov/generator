#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <QVector>
#include "manager.h"
#include "datastorage.h"
#include <memory>
#include "options.h"

class DataProcessor
{
    public:
    DataProcessor()  = default;
    virtual ~DataProcessor()  = default;
public:
    virtual QString quittance(){ return QString();}
    virtual void process() = 0;
    virtual void setFileManager(Manager* _m) {m = _m;}
    virtual void setStorage(QVector<DataStorage>* _s) {s = _s;}
    virtual void lock(bool){}
    virtual void setSettings(const Settings&) {}
    Manager* manager() {return m;}
protected:
    Manager* m;
    QVector<DataStorage>* s;
};


#endif // INTERPRETER_H
