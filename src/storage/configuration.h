#pragma once

#include <QString>
#include "datastorage.h"
#include <map>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


struct kernel_t
{
    size_t offset{0};
    QString name{};
};

struct SoftLoad
{
    unsigned short GA{0xffff};
    unsigned short LA{0xffff};
    unsigned long kernel_addr_rom{0xffffffff};
    unsigned long kernel_addr_ram{0xa0040000};
    unsigned long kernel_size{0x50000};
    unsigned long part_addr_rom[4]{0xffffffff,0xffffffff,0xffffffff,0xffffffff};
    unsigned long part_addr_ram[4]{0xa00a0000,0xffffffff,0xffffffff,0xffffffff};
    unsigned long part_size[4]{0xffffffff,0xffffffff,0xffffffff,0xffffffff};
};

class Configuration
{
public:
    Configuration(const QString& path);
    ~Configuration() = default;
    kernel_t    getKernel(const size_t &m_num);
    void        loadCfg(std::map<size_t, SoftLoad> &hash);
    QString     ComlineRom();
    size_t      BaseRomAddr();
    QString     BlockName();
    void        loadRomAddresses(QStringList &);
    void        setCurrentBlock(const BlockType& = BlockType::bis);
private:
    QJsonDocument qjsondocument;
    QJsonArray    qjsonarray;
    QJsonObject   currentBlock;
    SoftLoad      getCfg(const size_t& la_num);
};








