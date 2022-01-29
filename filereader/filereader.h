#ifndef TBLFILEREADER_H
#define TBLFILEREADER_H

#include <QObject>
#include <QFile>
#include <QDebug>
#include "abstractfilereader.h"

class FileManager : public AbstractFileManager
{
    Q_OBJECT
public:
    explicit FileManager(QObject *parent = nullptr);
    ~FileManager();
public slots:
    virtual QStringList readFile(const QString& path) override;
    virtual bool writeToFile(const QStringList &data) override;
    virtual void setFilePath(const QString& path) override;
};

#endif
