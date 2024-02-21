#ifndef SREMANAGER_H
#define SREMANAGER_H

#include "manager.h"

class SreManager : public Manager
{
public:
    explicit SreManager();
    QByteArrayList  read(const size_t& block_size,const QString& path = QString()) override;
    QByteArray      read(const QString& path = QString()) override;
    QStringList     read(bool* ok = nullptr,const QString& path = QString()) override;
    bool write(const QStringList &data) override;
    bool write(bool* ok = nullptr,const QString &data={}) override;
    //новый интерфейс
    bool beginWrite(const QString& path) override;
    void endWrite() override;
    void write(const QString& options,const QByteArrayList& data) override;
signals:
private:
    QString header{"S1"};
    size_t base_addr{0};
};

#endif // SREMANAGER_H
