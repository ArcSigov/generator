#include "configuration.h"
#include "filemanager.h"

Configuration::Configuration(const QString& path)
{
    FileManager f;
    auto cfg = f.read(path);
    QJsonParseError err;
    qjsondocument  = QJsonDocument::fromJson(cfg,&err);
    if (qjsondocument.isArray())
        qjsonarray = qjsondocument.array();
}

void Configuration::loadCfg(std::map<size_t,SoftLoad>& hash)
{
    for (const auto& num : currentBlock["la_addresses"].toArray())
    {
        auto line = getCfg(num.toInt());
        hash[line.LA] = line;
    }
}

QStringList Configuration::blockList()
{
    QStringList out;
    for (const auto& block : qAsConst(qjsonarray))
    {
        out.push_back(block.toObject()["block"].toString());
    }
    return out;
}

size_t Configuration::BaseRomAddr()
{
    return currentBlock["base_rom_addr"].toString().toUInt(nullptr,16);
}


void Configuration::setCurrentBlock(const QString& name)
{
    for (const auto& block : qAsConst(qjsonarray))
    {
        if (block.toObject()["block"] == name)
        {
            currentBlock = block.toObject();
            return;
        }
    }
}

kernel_t Configuration::getKernel(const size_t& _pos)
{
    kernel_t  out;
    for (const auto& kernel : currentBlock["kernels"].toArray())
    {
        for (const auto& pos : kernel.toObject()["module"].toArray())
        {
            if (pos.toInt() == _pos)
            {
                out.name   = kernel.toObject()["name"].toString();
                out.offset = kernel.toObject()["rom_offset"].toString().toUInt(nullptr,16);
            }
        }
    }
    return out;
}

SoftLoad Configuration::getCfg(const size_t& la_num)
{
    SoftLoad s;
    for (const auto& cfg : currentBlock["cfg"].toArray())
    {
        for (const auto& pos : cfg.toObject()["pos"].toArray())
        {
            for (const auto& la : pos.toObject()["LA"].toArray())
            {
                if (la.toInt() == la_num)
                {
                    s.GA               = pos.toObject()["GA"].toInt();
                    s.LA               = la.toInt();
                    s.kernel_addr_ram  = cfg.toObject()["kernel_addr_ram"].toString().toUInt(nullptr,16);
                    s.kernel_addr_rom  = cfg.toObject()["kernel_addr_rom"].toString().toUInt(nullptr,16);
                    s.kernel_size      = cfg.toObject()["kernel_size"].toString().toUInt(nullptr,16);
                    s.part1_addr_ram   = cfg.toObject()["part1_addr_ram"].toString().toUInt(nullptr,16);
                    s.part1_addr_rom   = cfg.toObject()["part1_addr_rom"].toString().toUInt(nullptr,16);
                    s.part1_size       = cfg.toObject()["part1_size"].toString().toUInt(nullptr,16);
                    s.part2_addr_ram   = cfg.toObject()["part2_addr_ram"].toString().toUInt(nullptr,16);
                    s.part2_addr_rom   = cfg.toObject()["part2_addr_rom"].toString().toUInt(nullptr,16);
                    s.part2_size       = cfg.toObject()["part2_size"].toString().toUInt(nullptr,16);
                    s.part3_addr_ram   = cfg.toObject()["part3_addr_ram"].toString().toUInt(nullptr,16);
                    s.part3_addr_rom   = cfg.toObject()["part3_addr_rom"].toString().toUInt(nullptr,16);
                    s.part3_size       = cfg.toObject()["part3_size"].toString().toUInt(nullptr,16);
                    s.config_addr_ram  = cfg.toObject()["config_addr_ram"].toString().toUInt(nullptr,16);
                    s.config_addr_rom  = cfg.toObject()["config_addr_rom"].toString().toUInt(nullptr,16);
                    s.config_size      = cfg.toObject()["config_size"].toString().toUInt(nullptr,16);
                    return s;
                }
            }
        }
    }
    return {};
}

QString Configuration::getLaName(const size_t& la_num)
{
    for (const auto& cfg : currentBlock["cfg"].toArray())
    {
        for (const auto& pos : cfg.toObject()["pos"].toArray())
        {
            for (const auto& la : pos.toObject()["LA"].toArray())
            {
                if (la.toInt() == la_num)
                {
                  return pos.toObject()["name"].toString();
                }
            }
        }
    }
    return {};
}



QString Configuration::BlockName()
{
   return currentBlock["block"].toString();
}


void  Configuration::loadRomAddresses(QStringList& addr)
{
    for (const auto& num : currentBlock["rom_str"].toArray())
        addr.push_back(num.toString());
}


QString Configuration::ComlineRom()
{
    return currentBlock["comline_rom"].toString();
}

size_t Configuration::cfgRomAddr()
{
    return currentBlock["cfg_rom_addr"].toString().toUInt(nullptr,16);
}
