#pragma once


#include <QFile>
#include <QDebug>
#include "manager.h"
#include <memory>

class FileManager : public Manager
{
public:
    explicit FileManager();
    ~FileManager() = default;
public:
    virtual QStringList read(const QString& path = QString()) override;
    virtual bool write(const QStringList &data) override;
    virtual void setFilePath(const QString& path) override;
private:
    std::unique_ptr<QFile> f;
};
