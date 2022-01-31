#ifndef BUTCHMANAGER_H
#define BUTCHMANAGER_H

#include <QObject>
#include <QDebug>
#include "manager.h"

class ButchManager : public Manager
{
    Q_OBJECT
public:
    explicit ButchManager(QObject *parent = nullptr);
    ~ButchManager();
public slots:
    virtual QStringList read(const QString& path = QString()) override;
    virtual bool write(const QStringList &data) override;
    virtual void setFilePath(const QString& path) override;
};

#endif
