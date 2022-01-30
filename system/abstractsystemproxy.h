#ifndef ABSTRACTSYSTEMPROXY_H
#define ABSTRACTSYSTEMPROXY_H

#include <QObject>

class AbstractSystemProxy : public QObject
{
    Q_OBJECT
public:
    explicit AbstractSystemProxy(QObject *parent = nullptr) : QObject(parent) {};
    ~AbstractSystemProxy(){};
    virtual void command(const QString& command) = 0;
};

#endif // ABSTRACTSYSTEMPROXY_H
