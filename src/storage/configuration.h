#pragma once

#include <QStringList>
#include <map>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <vector>


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
    unsigned long config_addr_rom{0xffffffff};
    unsigned long config_addr_ram{0xffffffff};
    unsigned long config_size{0xffffffff};
    unsigned long part1_addr_rom{0xffffffff};
    unsigned long part1_addr_ram{0xffffffff};
    unsigned long part1_size{0xffffffff};
    unsigned long part2_addr_rom{0xffffffff};
    unsigned long part2_addr_ram{0xffffffff};
    unsigned long part2_size{0xffffffff};
    unsigned long part3_addr_rom{0xffffffff};
    unsigned long part3_addr_ram{0xffffffff};
    unsigned long part3_size{0xffffffff};
};

struct block_t
{
    QString blockName;
    QString comlineRom;
    std::map<std::vector<size_t>,kernel_t> kernels;
    std::map<size_t, SoftLoad> cfg;
    QStringList romAddresses;
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
    size_t cfgRomAddr();
    QStringList blockList();
    void        loadRomAddresses(QStringList &);
    void        setCurrentBlock(const QString& name= " ");   
    QString     getLaName(const size_t& la_num);
private:
    QJsonDocument qjsondocument;
    QJsonArray    qjsonarray;
    QJsonObject   currentBlock;
    SoftLoad      getCfg(const size_t& la_num);
};








