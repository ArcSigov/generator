#include "cfgprocessor.h"
#include "tablerowprop.h"

CfgDataProcessor::CfgDataProcessor() : block (std::make_unique<BlockCfg>())
{

}

void CfgDataProcessor::process()
{
    if (!s) return;

    QStringList str(file_header);
    for (auto it = s->begin(); it != s->end(); it++)
        block->insert(it->at(MODULE_NUM).toUInt(),it->genericSize().toUInt(), it->at(RAM_ADDR).toUInt(), it->genericType(), it->at(PART_N).toUInt());

    for (auto i = 0ull; i < block->size(); i++)
    {
        auto p = block->at(i);
        str.push_back("\t{ 0x"+ QString::number(p.GA,16).toUpper().rightJustified(4,'0'));
        str.push_back(", 0x"  + QString::number(p.LA,16).rightJustified(4,'0'));
        str.push_back(", 0x"  + QString::number(p.kernel_addr_rom,16));
        str.push_back(", 0x"  + QString::number(p.kernel_addr_ram,16));
        str.push_back(", 0x"  + QString::number(p.kernel_size,16));
        for (auto j = 0 ; j < 4 ; j++)
        {
            str.push_back(", 0x"  + QString::number(p.part_addr_ram[j],16));
            str.push_back(", 0x"  + QString::number(p.part_addr_rom[j],16));
            str.push_back(", 0x"  + QString::number(p.part_size[j],16));
        }
        str.push_back("}");
        if (i+1 != block->size()) str.push_back(",");
        str.push_back("\r\n");
    }
    str.push_back("};");

    if (m)
    {
        m->setFilePath(outcfgname);
        m->write(str);
    }
}

void CfgDataProcessor::setSettings(const Settings& _settings)
{
    outcfgname.clear();
    outcfgname.push_back(_settings.abspath+"/");
    switch (_settings.type)
    {
    case BlockType::bis:
        outcfgname.push_back("cfg_bis.c");
        block = std::make_unique<BisCfg>();
        break;
    case BlockType::bcvm:
        outcfgname.push_back("cfg_bcvm.c");
        block = std::make_unique<BcvmCfg>();
        break;
    case BlockType::bgs:
        outcfgname.push_back("cfg_bgs.c");
        block = std::make_unique<BgsCfg>();
        break;
    case BlockType::undef:
        block = std::make_unique<BlockCfg>();
        break;
    default:break;
    }
}
