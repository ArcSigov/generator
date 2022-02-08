#ifndef INIDATAINTERPRETER_H
#define INIDATAINTERPRETER_H

#include <QObject>
#include <QDebug>
#include "dataprocessor.h"
#include "datastorage.h"

class IniDataProcessor : public DataProcessor
{
public:
    IniDataProcessor() = default;
    ~IniDataProcessor() = default;
    virtual void process() override;
    virtual void setSettings(const Settings&) override;
    virtual QString quittance() override;
private:
    QString output_directory;
};

#endif
