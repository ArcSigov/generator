#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <QObject>
#include <QVector>
#include "manager.h"
#include "datastorage.h"

class FileDataInterpreter : public QObject
{
    Q_OBJECT
    public:
    explicit FileDataInterpreter(QObject *parent = nullptr) : QObject(parent){};
    ~FileDataInterpreter() {};
public:
    virtual void read() = 0;
    virtual void write(DataStorage* storage = nullptr) = 0;
    void setFileManager(Manager* _manager) {m = _manager;}
    Manager* manager() const {return m;}
signals:
    void status(const QString& status);
protected:
    Manager* m;
};

#endif // INTERPRETER_H
