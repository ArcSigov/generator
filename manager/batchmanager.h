#pragma once


#include <QDebug>
#include "manager.h"

class BatchManager : public Manager
{
public:
    BatchManager() = default;
    ~BatchManager()  = default;
public slots:
    virtual QStringList read(const QString& path = QString()) override;
    virtual bool write(const QStringList &data) override;
    virtual void setFilePath(const QString& path) override;
};
