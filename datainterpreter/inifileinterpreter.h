#ifndef INIFILEINTERPRETER_H
#define INIFILEINTERPRETER_H

#include <QObject>
#include <QDebug>
#include "interpreter.h"
#include "datastorage.h"

class IniDataInterpreter : public FileDataInterpreter
{
    Q_OBJECT
public:
    explicit IniDataInterpreter(QVector<DataStorage>* s = nullptr,QObject* parent = nullptr);
    ~IniDataInterpreter();
    virtual void readFileData(const QStringList& l) override;
    virtual QStringList interpreteToFileData() override;
private:
    QVector<DataStorage>* v;
    QString genResult;
};

#endif
