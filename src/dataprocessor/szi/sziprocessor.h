#ifndef SZIPROCESSOR_H
#define SZIPROCESSOR_H


#include "dataprocessor.h"

class SziDataProcessor : public DataProcessor
{
    Q_OBJECT
public:
    explicit SziDataProcessor(DataProcessor* _sre,QObject *parent = nullptr);
    void process();
signals:
private:
    DataProcessor* sre;
    QString getStrCpu(size_t la);
    QString getStrPos(size_t pos);
};

#endif // SZIPROCESSOR_H
