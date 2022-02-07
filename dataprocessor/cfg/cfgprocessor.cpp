#include "cfgprocessor.h"
#include "tablerowprop.h"

CfgDataProcessor::CfgDataProcessor() : type (BlockType::undef)
{

}

void CfgDataProcessor::process()
{
    if (type == BlockType::undef || !s) return;

    for (auto it = s->begin(); it != s->end(); it++)
    {
        auto soft = block->makeCfg(it->at(MODULE_NUM).toUInt(),it->genericSize().toUInt(), it->at(RAM_ADDR).toUInt(), it->genericType(), it->at(PART_N).toUInt());
        cfglist[soft.GA] = soft;
    }
}

void CfgDataProcessor::setBlockType(const BlockType& type)
{
    if (type == BlockType::undef) return;

    cfglist.clear();
    switch (type)
    {
    case BlockType::bis:
        m->setFilePath("cfg_bis.c");
        block = std::make_unique<BisCfg>();
        break;
    case BlockType::bcvm:
        m->setFilePath("cfg_bcvm.c");
        block = std::make_unique<BcvmCfg>();
        break;
    case BlockType::bgs:
        m->setFilePath("cfg_bgs.c");
        block = std::make_unique<BgsCfg>();
        break;
    case BlockType::undef:
        break;
    default:break;
    }
}

SoftLoad BisCfg::makeCfg(const size_t& pos, const size_t& size, const size_t& ram_addr, const bool& is_part, const size_t& npart)
{
    auto kernel_addr_rom = (pos == 0x25 || pos == 0x49 ? 0xb0000000 :
                            pos == 0x29 || pos == 0x45 ? 0xb0080000 :
                            pos >= 0x29 && pos <= 0x45 ? 0xb0100000 : 0);


    SoftLoad s(1,pos,kernel_addr_rom,kernel_addr_ram,kernel_size);
    return s;
}
