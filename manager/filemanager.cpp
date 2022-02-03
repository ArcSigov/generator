#include "filemanager.h"


FileManager::FileManager() : f(std::make_unique<QFile>())
{

}


QStringList FileManager::read(const QString &path)
{
    setFilePath(path);
    if (f->open(QIODevice::ReadOnly))
    {
        QStringList l;
        QTextStream s(f.get());
        while (!s.atEnd())
        {
            l.push_back(s.readLine());
        }
        f->close();
        return l;
    }
    return {};
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
