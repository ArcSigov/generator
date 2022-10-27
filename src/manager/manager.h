#pragma once


#include <QFile>
#include <QDebug>
#include <QByteArray>


class Manager
{
public:
    Manager() = default;
    virtual ~Manager() = default;
    virtual QByteArrayList  read(const size_t& block_size,const QString& path = QString()) = 0;
    virtual QByteArray      read(const QString& path = QString()) = 0;
    virtual QStringList     read(bool* ok = nullptr,const QString& path = QString()) = 0;
    virtual bool write(const QStringList &data) = 0;
    virtual bool write(const QString &data) = 0;
    virtual void setFilePath(const QString& path) = 0;
};
