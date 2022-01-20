#ifndef TBLFILEINTERPRETER_H
#define TBLFILEINTERPRETER_H

#include <QObject>
#include <QDebug>
#include "interpreter.h"
#include "datastorage.h"

class TblFileInterpreter : public FileDataInterpreter
{
    Q_OBJECT
public:
    explicit TblFileInterpreter(QVector<DataStorage>* s = nullptr,QObject* parent = nullptr);
    ~TblFileInterpreter();
    virtual void readFileData(const QVector<QStringList>& l) override;
private:
    QVector<DataStorage>* v;
};

#endif // TBLFILEINTERPRETER_H
