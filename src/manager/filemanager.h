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
    bool write(const QString &data) override
    {

    }
    void setFilePath(const QString& path) override;
private:
    std::unique_ptr<QFile> f;
};
