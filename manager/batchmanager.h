#ifndef BUTCHMANAGER_H
#define BUTCHMANAGER_H


#include <QDebug>
#include "manager.h"

class BatchManager : public Manager
{
public:
    explicit BatchManager() = default;
    ~BatchManager()  = default;
public slots:
    virtual QStringList read(const QString& path = QString()) override;
    virtual bool write(const QStringList &data) override;
    virtual void setFilePath(const QString& path) override;
};

#endif
