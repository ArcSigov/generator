#include "configuration.h"
#include "filemanager.h"

Configuration::Configuration(const QString& path)
{
    FileManager f;
    QByteArray ba;
    for (const auto& it : f.read(path))
        ba.append(it);

    QJsonParseError err;
    qjsondocument  = QJsonDocument::fromJson(ba,&err);
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

size_t Configuration::BaseRomAddr()
{
    return currentBlock["base_rom_addr"].toString().toUInt(nullptr,16);
}


void Configuration::setCurrentBlock(const BlockType& type)
{
    for (const auto& block : qAsConst(qjsonarray))
    {
        switch (type)
        {
            case BlockType::bis:
            if (block.toObject()["block"] == "bis")
            {
                currentBlock = block.toObject();
                return;
            }
            case BlockType::bcvm:
            if (block.toObject()["block"] == "bcvm")
            {
                currentBlock = block.toObject();
                return;
            }
            case BlockType::bgs:
            if (block.toObject()["block"] == "bgs")
            {
                currentBlock = block.toObject();
                return;
            }
            case BlockType::undef:
            default:
                break;
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
                    s.part_addr_ram[0] = cfg.toObject()["part1_addr_ram"].toString().toUInt(nullptr,16);
                    s.part_addr_rom[0] = cfg.toObject()["part1_addr_rom"].toString().toUInt(nullptr,16);
                    s.part_size[0]     = cfg.toObject()["part1_size"].toString().toUInt(nullptr,16);
                    s.part_addr_ram[1] = cfg.toObject()["part2_addr_ram"].toString().toUInt(nullptr,16);
                    s.part_addr_rom[1] = cfg.toObject()["part2_addr_rom"].toString().toUInt(nullptr,16);
                    s.part_size[1]     = cfg.toObject()["part2_size"].toString().toUInt(nullptr,16);
                    s.part_addr_ram[2] = cfg.toObject()["part3_addr_ram"].toString().toUInt(nullptr,16);
                    s.part_addr_rom[2] = cfg.toObject()["part3_addr_rom"].toString().toUInt(nullptr,16);
                    s.part_size[2]     = cfg.toObject()["part3_size"].toString().toUInt(nullptr,16);
                    s.part_addr_ram[3] = cfg.toObject()["config_addr_ram"].toString().toUInt(nullptr,16);
                    s.part_addr_rom[3] = cfg.toObject()["config_addr_rom"].toString().toUInt(nullptr,16);
                    s.part_size[3]     = cfg.toObject()["config_size"].toString().toUInt(nullptr,16);
                    return s;
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
