#include "batchmanager.h"


bool BatchManager::write(const QStringList &data)
{
    for (const auto &it: data)
    {
        QString command = "cmd.exe /C " + it;
        std::system(command.toStdString().c_str());
    }
    return true;
}

void BatchManager::setFilePath(const QString& path)
{
   Q_UNUSED(path)
}
