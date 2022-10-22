#include "manager.h"


class SreManager : public Manager
{
public:
    SreManager(size_t _block_size) : block_size(_block_size){}
    ~SreManager(){}
    bool write(const QStringList &data) override;
    QStringList read(const QString& path = QString()) override;
    void setFilePath(const QString& path) override;
private:
    size_t block_size;
};
