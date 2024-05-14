#pragma once


#include <QFile>
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
    virtual bool write(bool*ok = nullptr,const QString& data= {}) = 0;
    void setFilePath(const QString& path)
    {
        if (!path.isEmpty()) f.setFileName(path);
    }
    virtual bool beginWrite(const QString& path) = 0;
    virtual void endWrite() = 0;
    virtual void write(const QString& options,const QByteArrayList& data) = 0;    
protected:
    QFile f;
};
