#pragma once


#include <QDebug>
#include "manager.h"

class BatchManager : public Manager
{
public:
    BatchManager() = default;
    ~BatchManager()  = default;
public slots:
    QByteArrayList  read(const size_t& block_size,const QString& path = QString()) override {};
    QByteArray      read(const QString& path = QString()) override {};
    QStringList     read(bool* ok = nullptr,const QString& path = QString()) override {};
    bool write(const QStringList &data) override;
    bool write(const QString &data) override
    {

    }
    void setFilePath(const QString& path) override;
};
