#pragma once


#include <QFile>
#include <QDebug>


class Manager
{
public:
    Manager() = default;
    virtual ~Manager() = default;
    virtual QStringList read(const QString& path = QString()) = 0;
    virtual bool write(const QStringList &data) = 0;
    virtual void setFilePath(const QString& path) = 0;
};
