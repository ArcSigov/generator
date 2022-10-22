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

//    if (settings.romKernelsFpo_enabled) formatted.push_back(settings.kernelflashstr);

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

        if (cur_ga != hash[it.at(MODULE_NUM).toUInt()].GA)
        {
            cur_ga  = hash[it.at(MODULE_NUM).toUInt()].GA;
            auto kernel = Storage::load()->cfg().getKernel(cur_ga);
            formatted.push_back(QString::number(cur_ga) +   //module
                                " 1 " +                                            //always 1
                                QString::number(it.at(MODULE_NUM).toUInt(),16) +   //la
                                " a0040000"+                                       //start ram addr always const
                                " 0"       +                                       // mot or elf
                                " 00000000 " +
                                Storage::load()->options().kernelpath + "/" + kernel.name + "\r\n");             //abs path
        }

        formatted.push_back(QString::number(cur_ga) +   //module
                            " 1 " +                                             //always 1
                            QString::number(it.at(MODULE_NUM).toUInt(),16) +    //la
                            " a0040000 "+                                       //start ram addr always const
                            QString::number(!it.genericType()) +                // mot or elf
                            " " + QString::number(it.at(RAM_ADDR).toUInt(),16) +
                            " " +
                            it.at(FILE_PATH).toString() + "\r\n");             //abs path
    }
    if (manager)
    {
        manager->setFilePath(Storage::load()->options().loadpath + "/sw_load_" + Storage::load()->cfg().BlockName() + "_ram.txt");
        manager->write(formatted);
    }
}

