#ifndef TBLFILEINTERPRETER_H
#define TBLFILEINTERPRETER_H

#include <QObject>
#include <QDebug>
#include "interpreter.h"
#include "datastorage.h"

class TblDataInterpreter : public FileDataInterpreter
{
    Q_OBJECT
public:
    explicit TblDataInterpreter(QVector<DataStorage>* s = nullptr,QObject* parent = nullptr);
    ~TblDataInterpreter();
    virtual void readFileData(const QVector<QStringList>& l) override;
    virtual void interpreteToFileData(bool) override;
private:
    QVector<DataStorage>* v;
};

#endif
