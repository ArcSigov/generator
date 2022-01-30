#include "winsystemproxy.h"

WinSystemProxy::WinSystemProxy(QObject *parent) : AbstractSystemProxy(parent)
{

}

WinSystemProxy::~WinSystemProxy()
{

}

void WinSystemProxy::command(const QString &command)
{
    QString base = "cmd.exe /C ";
    base +=command;
    std::system(command.toStdString().c_str());
}
