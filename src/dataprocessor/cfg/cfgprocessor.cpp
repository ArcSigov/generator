#include "cfgprocessor.h"
#include "tablerowprop.h"

/*!
Выполняет генерацию конфигурационного блока для выбранного блока
*/
void CfgDataProcessor::process()
{
    QStringList str;
    str.push_back(file_header);

    std::map<size_t,SoftLoad> hash;
    Storage::load()->cfg().loadCfg(hash);

    for (const auto& it : Storage::load()->data())
    {
          auto m_num = it.at(MODULE_NUM).toUInt();
          auto p_num = it.at(PART_N).toUInt();
          hash[m_num].part_addr_rom[p_num] = it.romAddr();
          hash[m_num].part_addr_ram[p_num] = it.at(RAM_ADDR).toUInt();
          hash[m_num].part_size[p_num]     = it.fileSize();
    }

    for (auto it = hash.begin(); it != hash.end();)
    {
       str.push_back("\t{ 0x"+ QString::number(it->second.GA,16).toUpper().rightJustified(4,'0'));
       str.push_back(", 0x"  + QString::number(it->second.LA,16).rightJustified(4,'0'));
       str.push_back(", 0x"  + QString::number(it->second.kernel_addr_rom,16));
       str.push_back(", 0x"  + QString::number(it->second.kernel_addr_ram,16));
       str.push_back(", 0x"  + QString::number(it->second.kernel_size,16).rightJustified(8,'0'));
       for (auto j = 0 ; j < 4 ; j++)
       {
           str.push_back(", 0x"  + QString::number(it->second.part_addr_rom[j],16));
           str.push_back(", 0x"  + QString::number(it->second.part_addr_ram[j],16));
           str.push_back(", 0x"  + QString::number(it->second.part_size[j],16).rightJustified(8,'0'));
       }
       str.push_back("}");
       if (++it != hash.end()) str.push_back(",");
       str.push_back("\r\n");
    }
    str.push_back("};");

    if (manager)
    {
        manager->setFilePath(Storage::load()->options().loadpath + "/cfg_" + Storage::load()->cfg().BlockName() + ".c");
        manager->write(str);
    }
}
