#ifndef WINSYSTEMPROXY_H
#define WINSYSTEMPROXY_H

#include <QObject>
#include "abstractsystemproxy.h"

class WinSystemProxy : public AbstractSystemProxy
{
    Q_OBJECT
public:
    explicit WinSystemProxy(QObject *parent = nullptr);
    ~WinSystemProxy();
    virtual void command(const QString& command) override;
};

#endif
