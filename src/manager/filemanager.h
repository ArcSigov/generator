#pragma once


#include <QFile>
#include "manager.h"
#include <memory>

class FileManager : public Manager
{
public:
    explicit FileManager();
    ~FileManager() = default;
public:
    QStringList     read(bool* ok = nullptr,const QString& path = QString()) override;
    QByteArrayList  read(const size_t& block_size,const QString& path = QString()) override;
    QByteArray      read(const QString& path = QString()) override;
    bool write(const QStringList &data) override;
    bool write(bool* ok = nullptr,const QString &data = {}) override
    {
        return false;
    }
    virtual bool beginWrite(const QString& path) override
    {
        return true;
    };
    virtual void endWrite() override{}
    virtual void write(const QString& options,const QByteArrayList& data) override{}
};
