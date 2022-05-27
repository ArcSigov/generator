#include "txtdataprocessor.h"


/*!
Выполняет генерацию загрузочного файла для интерфейса RS в ПЗУ
*/
void FlashRsTxtDataProcessor::process()
{
    QStringList formatted;
    auto i = 1;

    for (const auto& it : Storage::load()->data())
    {
        if(it.at(IS_CHECKED).toBool())
            formatted.push_back(QString::number(i++) + " 0 " + QString::number(it.romAddr(),16) + " " + Storage::load()->options().loadpath + "/" + it.genericName() + "\r\n");
    }

    auto last = Storage::load()->data().back().romAddr() + Storage::load()->data().back().fileSize();
    while (last % 0x40000 != 0)
        last++;

    formatted.push_front("0 f " + QString::number(Storage::load()->data().front().romAddr(),16) + "-" + QString::number(last,16)+"\r\n");
    formatted.push_back(QString::number(i++) + " f " + Storage::load()->cfg().cfgRomAddr() +"\r\n");
    formatted.push_back(QString::number(i) + " 0 00000000 " + Storage::load()->options().loadpath + "/cfg_" + Storage::load()->cfg().BlockName() + ".mot\r\n");


    if (manager)
    {
        manager->setFilePath(Storage::load()->options().loadpath + "/rs_load_"+Storage::load()->cfg().BlockName()+"_rom.txt");
        manager->write(formatted);
    }
}
