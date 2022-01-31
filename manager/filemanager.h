#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QFile>
#include <QDebug>
#include "manager.h"

class FileManager : public Manager
{
    Q_OBJECT
public:
    explicit FileManager(QObject *parent = nullptr);
    ~FileManager();
public slots:
    virtual QStringList read(const QString& path = QString()) override;
    virtual bool write(const QStringList &data) override;
    virtual void setFilePath(const QString& path) override;
private:
    QFile *f;
};

#endif
