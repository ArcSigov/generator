#ifndef MANAGER_H
#define MANAGER_H


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


#endif
