#include "butchmanager.h"


ButchManager::ButchManager(QObject* parent) :
    Manager(parent)
{

}

ButchManager::~ButchManager()
{

}

QStringList ButchManager::read(const QString &path)
{
    Q_UNUSED(path)
    return {};
}

bool ButchManager::write(const QStringList &data)
{
    for (const auto &it: data)
    {
        QString command = "cmd.exe /C " + it;
        std::system(command.toStdString().c_str());
    }
    return true;
}

void ButchManager::setFilePath(const QString& path)
{
   Q_UNUSED(path)
}
