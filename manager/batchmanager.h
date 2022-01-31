#ifndef BUTCHMANAGER_H
#define BUTCHMANAGER_H

#include <QObject>
#include <QDebug>
#include "manager.h"

class BatchManager : public Manager
{
    Q_OBJECT
public:
    explicit BatchManager(QObject *parent = nullptr);
    ~BatchManager();
public slots:
    virtual QStringList read(const QString& path = QString()) override;
    virtual bool write(const QStringList &data) override;
    virtual void setFilePath(const QString& path) override;
};

#endif
