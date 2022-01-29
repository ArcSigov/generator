#ifndef TBLFILEREADER_H
#define TBLFILEREADER_H

#include <QObject>
#include <QFile>
#include <QDebug>
#include "filereader.h"

class TblFileManager : public FileManager
{
    Q_OBJECT
public:
    explicit TblFileManager(QObject *parent = nullptr);
    ~TblFileManager();
public slots:
    virtual void readFile(const QString& path) override;
    virtual bool writeToFile(const QStringList &data) override;
    virtual void setFilePath(const QString& path) override;
};

#endif
