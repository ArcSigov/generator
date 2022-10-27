#include "filemanager.h"
#include <QDataStream>

FileManager::FileManager() : f(std::make_unique<QFile>())
{

}


QStringList FileManager::read(bool* ok,const QString& path)
{
    Q_UNUSED(ok)
    setFilePath(path);
    QStringList out;
    if (f->open(QIODevice::ReadOnly))
    {
        QTextStream s(f.get());
        while (!s.atEnd())
            out.push_back(s.readLine());
        f->close();
    }
    return out;
}

QByteArrayList  FileManager::read(const size_t& block_size,const QString& path)
{
    QByteArrayList out;
    setFilePath(path);
    if (f->open(QIODevice::ReadOnly))
    {
        while (!f->atEnd())
            out.push_back(f->read(block_size));
        f->close();
    }
    return out;
}


QByteArray FileManager::read(const QString& path)
{
    QByteArray out;
    setFilePath(path);
    if (f->open(QIODevice::ReadOnly))
    {
        out = f->readAll();
        f->close();
    }
    return out;
}


bool FileManager::write(const QStringList &data)
{
    if(!f->open(QIODevice::WriteOnly | QIODevice::Truncate))
        return false;

    QTextStream stream(f.get());
    for (const auto& it: data)
        stream << it;

    f->close();
    return true;
}

void FileManager::setFilePath(const QString& path)
{
    if (!path.isEmpty())  f->setFileName(path);
}
