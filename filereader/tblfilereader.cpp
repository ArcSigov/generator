#include "tblfilereader.h"


TblFileManager::TblFileManager(QObject* parent) :
    FileManager(parent)
{

}

TblFileManager::~TblFileManager()
{

}

void TblFileManager::readFile(const QString &path)
{
    f->setFileName(path);
    if (f->open(QIODevice::ReadOnly))
    {
        QVector<QStringList> l;
        QTextStream s(f);
        while (!s.atEnd())
        {
            auto string = s.readLine();
            l.push_back(string.split(";"));
        }
        f->close();
        emit readResult(l);
    }
}

bool TblFileManager::writeToFile(const QStringList &data)
{
    if(f->open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QTextStream stream(f);
        for (const auto& it: data)
        {
            stream << it;
        }
        f->close();
        emit saveResult(true);
    }
    emit saveResult(false);
    return false;
}

void TblFileManager::setFilePath(const QString& path)
{
    if (!path.isEmpty())
    {
        f->setFileName(path);
        emit getDataToWrite(true);
    }
}
