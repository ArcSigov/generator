#include "txtdataprocessor.h"

/*!
Выполняет генерацию загрузочного файла для интерфейса SW в ПЗУ
*/
void FlashSwTxtDataProcessor::process()
{
    QStringList formatted;
    QStringList rom_addr;
    Storage::load()->cfg().loadRomAddresses(rom_addr);
    auto cfgstr = Storage::load()->options().loadpath + "/cfg_" +Storage::load()->cfg().BlockName()+".mot\r\n";

    for (const auto& it : Storage::load()->data())
    {
        if(!it.at(IS_CHECKED).toBool())
            continue;

        auto str = QString::number(it.romAddr(),16) + " " + Storage::load()->options().loadpath + "/" + it.genericName() + "\r\n";
        for (const auto& addr : qAsConst(rom_addr))
        {
            formatted.push_back(addr + " f " + str);
            formatted.push_back(addr + " 0 " + str);
        }
    }

    for (const auto& it : qAsConst(rom_addr))
    {
        formatted.push_back(it + " f 00000000 " + cfgstr);
        formatted.push_back(it + " 0 00000000 " + cfgstr);
    }
    if (manager)
    {
        manager->setFilePath(Storage::load()->options().loadpath + "/sw_load_" + Storage::load()->cfg().BlockName() + "_rom.txt");
        manager->write(formatted);
    }
}


/*!
Выполняет генерацию загрузочного файла для интерфейса SW в ОЗУ
*/
void RamSwTxtDataProcessor::process()
{
    QStringList formatted;
    std::map<size_t,SoftLoad> hash;
    Storage::load()->cfg().loadCfg(hash);
    auto cur_ga = 0;
    for (const auto& it : Storage::load()->data())
    {
        if(!it.at(IS_CHECKED).toBool())
            continue;

        auto module_nums = it.at(MODULE_NUM).toString().split(',');

        for (const auto& module_num:module_nums)
        {
            if (cur_ga != hash[module_num.toUInt(nullptr,16)].GA)
            {
                cur_ga  = hash[module_num.toUInt(nullptr,16)].GA;
                auto kernel = Storage::load()->cfg().getKernel(cur_ga);
                formatted.push_back(QString::number(cur_ga) +   //module
                                    " 1 " +                                            //always 1
                                    module_num +                                       //la
                                    " a0040000"+                                       //start ram addr always const
                                    " 0"       +                                       // mot or elf
                                    " 00000000 " +
                                    Storage::load()->options().kernelpath + "/" + kernel.name + "\r\n");             //abs path
            }

            formatted.push_back(QString::number(cur_ga) +   //module
                                " 1 " +                                             //always 1
                                module_num +                                        //la
                                " a0040000 "+                                       //start ram addr always const
                                QString::number(!it.genericType()) +                // mot or elf
                                " " + QString::number(it.at(RAM_ADDR).toUInt(),16) +
                                " " +
                                it.at(FILE_PATH).toString() + "\r\n");             //abs path
        }
    }

    std::sort(formatted.begin(),formatted.end(),[](const QString& current, const QString& next){

        auto currentlist = current.split(" ");
        auto nextlist = next.split(" ");
        if (currentlist[0].toUInt(nullptr,10) ==  nextlist[0].toUInt(nullptr,10))
        {
            return currentlist[5].toUInt(nullptr,16) <  nextlist[5].toUInt(nullptr,16);
        }
        return currentlist[0].toUInt(nullptr,10) < nextlist[0].toUInt(nullptr,10);
    });

    for (auto first = formatted.begin(); first!=formatted.end();first++)
    {
        for (auto next = first+1; next!=formatted.end();next++)
        {
            if (*first == *next)
            {
                formatted.erase(next);
                first = formatted.begin();
                break;
            }
        }
    }

    if (manager)
    {
        manager->setFilePath(Storage::load()->options().loadpath + "/sw_load_" + Storage::load()->cfg().BlockName() + "_ram.txt");
        manager->write(formatted);
    }
}

