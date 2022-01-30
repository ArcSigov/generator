#ifndef BUTCHINTERPRETER_H
#define BUTCHINTERPRETER_H

#include <QObject>
#include <QDebug>
#include "interpreter.h"
#include "datastorage.h"

class ButchInterpreter : public FileDataInterpreter
{
    Q_OBJECT
public:
    explicit ButchInterpreter(QVector<DataStorage> *s = nullptr, QObject* parent = nullptr);
    ~ButchInterpreter();
    virtual void readFileData(const QStringList& l) override;
    virtual QStringList interpreteToFileData() override;
private:
    QVector<DataStorage> *v;
};

#endif
