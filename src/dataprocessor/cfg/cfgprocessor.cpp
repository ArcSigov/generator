#include "cfgprocessor.h"
#include "tablerowprop.h"

/*!
Выполняет генерацию конфигурационного блока для выбранного блока
*/
void CfgDataProcessor::process()
{
    QStringList str;
    str.push_back(settings.file_header);

    switch (settings.type)
    {
        case BlockType::bis:    block = std::make_unique<BisCfg>();     break;
        case BlockType::bcvm:   block = std::make_unique<BcvmCfg>();    break;
        case BlockType::bgs:    block = std::make_unique<BgsCfg>();     break;
        case BlockType::undef:  block = std::make_unique<BlockCfg>();   break;
        default:break;
    }

    block->clear();
    for (auto it = storage.begin(); it != storage.end(); it++)
        block->insert(it->at(MODULE_NUM).toUInt(),it->romAddr(),it->at(RAM_ADDR).toUInt(), it->fileSize(), it->at(PART_N).toUInt());

    for (auto i = 0ull; i < block->size(); i++)
    {
        auto p = block->at(i);
        str.push_back("\t{ 0x"+ QString::number(p.GA,16).toUpper().rightJustified(4,'0'));
        str.push_back(", 0x"  + QString::number(p.LA,16).rightJustified(4,'0'));
        str.push_back(", 0x"  + QString::number(p.kernel_addr_rom,16));
        str.push_back(", 0x"  + QString::number(p.kernel_addr_ram,16));
        str.push_back(", 0x"  + QString::number(p.kernel_size,16).rightJustified(8,'0'));
        for (auto j = 0 ; j < 4 ; j++)
        {
            str.push_back(", 0x"  + QString::number(p.part_addr_ram[j],16));
            str.push_back(", 0x"  + QString::number(p.part_addr_rom[j],16));
            str.push_back(", 0x"  + QString::number(p.part_size[j],16).rightJustified(8,'0'));
        }
        str.push_back("}");
        if (i+1 != block->size()) str.push_back(",");
        str.push_back("\r\n");
    }
    str.push_back("};");

    if (manager)
    {
        manager->setFilePath(settings.commandHeader[CFG_NAME]);
        manager->write(str);
    }
}
