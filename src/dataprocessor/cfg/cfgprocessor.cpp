#include "cfgprocessor.h"
#include "tablerowprop.h"
#include "sreprocessor.h"

/*!
Выполняет генерацию конфигурационного блока для выбранного блока
*/
void CfgDataProcessor::process()
{
    QStringList str;
    QByteArrayList list;
    str.push_back(file_header);

    std::map<size_t,SoftLoad> hash;
    Storage::load()->cfg().loadCfg(hash);

    for (const auto& it : Storage::load()->data())
    {
          auto m_nums = it.at(MODULE_NUM).toString().split(',');
          auto p_num = it.at(PART_N).toUInt();
          for (const auto& m_num: m_nums)
          {              
              switch(p_num)
              {
                case 0:
                    hash[m_num.toUInt(nullptr,16)].config_addr_rom = it.romAddr();
                    hash[m_num.toUInt(nullptr,16)].config_addr_ram = it.at(RAM_ADDR).toUInt();
                    hash[m_num.toUInt(nullptr,16)].config_size     = it.fileSize();
                    break;
                case 1:
                    hash[m_num.toUInt(nullptr,16)].part1_addr_rom = it.romAddr();
                    hash[m_num.toUInt(nullptr,16)].part1_addr_ram = it.at(RAM_ADDR).toUInt();
                    hash[m_num.toUInt(nullptr,16)].part1_size     = it.fileSize();
                    break;
                case 2:
                    hash[m_num.toUInt(nullptr,16)].part2_addr_rom = it.romAddr();
                    hash[m_num.toUInt(nullptr,16)].part2_addr_ram = it.at(RAM_ADDR).toUInt();
                    hash[m_num.toUInt(nullptr,16)].part2_size     = it.fileSize();
                    break;
                case 3:
                    hash[m_num.toUInt(nullptr,16)].part3_addr_rom = it.romAddr();
                    hash[m_num.toUInt(nullptr,16)].part3_addr_ram = it.at(RAM_ADDR).toUInt();
                    hash[m_num.toUInt(nullptr,16)].part3_size     = it.fileSize();
                    break;
                default:break;
              }
          }
    }
    hash[0xff] = SoftLoad();
    hash[0xff].kernel_addr_ram = 0xffffffff;
    hash[0xff].kernel_size = 0xffffffff;

    for (auto it = hash.begin(); it != hash.end();it++)
    {
       list.push_back(QByteArray(static_cast<char*>(static_cast<void*>(&it->second)),16));
       list.push_back(QByteArray(static_cast<char*>(static_cast<void*>(&it->second))+16,16));
       list.push_back(QByteArray(static_cast<char*>(static_cast<void*>(&it->second))+32,16));
       list.push_back(QByteArray(static_cast<char*>(static_cast<void*>(&it->second))+48,16));

       if (it!=hash.begin())
           str.push_back(",\r\n");

       str.push_back("\t{ 0x"+ QString::number(it->second.GA,16).toUpper().rightJustified(4,'0'));
       str.push_back(", 0x"  + QString::number(it->second.LA,16).rightJustified(4,'0'));
       str.push_back(", 0x"  + QString::number(it->second.kernel_addr_rom,16));
       str.push_back(", 0x"  + QString::number(it->second.kernel_addr_ram,16));
       str.push_back(", 0x"  + QString::number(it->second.kernel_size,16).rightJustified(8,'0'));
       str.push_back(", 0x"  + QString::number(it->second.config_addr_rom,16));
       str.push_back(", 0x"  + QString::number(it->second.config_addr_ram,16));
       str.push_back(", 0x"  + QString::number(it->second.config_size,16).rightJustified(8,'0'));
       str.push_back(", 0x"  + QString::number(it->second.part1_addr_rom,16));
       str.push_back(", 0x"  + QString::number(it->second.part1_addr_ram,16));
       str.push_back(", 0x"  + QString::number(it->second.part1_size,    16).rightJustified(8,'0'));
       str.push_back(", 0x"  + QString::number(it->second.part2_addr_rom,16));
       str.push_back(", 0x"  + QString::number(it->second.part2_addr_ram,16));
       str.push_back(", 0x"  + QString::number(it->second.part2_size,16).rightJustified(8,'0'));
       str.push_back(", 0x"  + QString::number(it->second.part3_addr_rom,16));
       str.push_back(", 0x"  + QString::number(it->second.part3_addr_ram,16));
       str.push_back(", 0x"  + QString::number(it->second.part3_size,16).rightJustified(8,'0'));
       str.push_back("}");
    }
    str.push_back("\r\n};\r\n");
    if (manager)
    {
        QStringList srec;       
        manager->setFilePath(Storage::load()->options().loadpath + "/cfg_" + Storage::load()->cfg().BlockName() + ".c");
        manager->write(str);
    }

    if (sre && sre->beginWrite(Storage::load()->options().loadpath + "/cfg_" + Storage::load()->cfg().BlockName() + ".mot"))
    {
        sre->write("rec_type:S3,base_addr:"+QString::number(Storage::load()->cfg().cfgRomAddr(),16),list);
        sre->endWrite();
    }
}
