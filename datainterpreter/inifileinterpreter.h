#ifndef INIDATAINTERPRETER_H
#define INIDATAINTERPRETER_H

#include <QObject>
#include <QDebug>
#include "interpreter.h"
#include "datastorage.h"

class IniDataInterpreter : public FileDataInterpreter
{
    Q_OBJECT
public:
    explicit IniDataInterpreter(QObject* parent = nullptr);
    ~IniDataInterpreter();
    virtual void read() override;
    virtual void write(DataStorage* storage = nullptr) override;
private:
    QVector<DataStorage>* v;
};

#endif
