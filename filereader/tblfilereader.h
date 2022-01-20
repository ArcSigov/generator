#ifndef TBLFILEREADER_H
#define TBLFILEREADER_H

#include <QObject>
#include <QFile>
#include <QDebug>
#include "filereader.h"

class TblFileReader : public FileReader
{
    Q_OBJECT
public:
    explicit TblFileReader(QObject *parent = nullptr);
    ~TblFileReader();
public slots:
    virtual void readFile(const QString& path) override;

};

#endif // ABSTRACTFILESYSTEM_H
