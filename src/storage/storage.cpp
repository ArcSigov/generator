#include "storage.h"

Storage* Storage::load()
{
    static Storage s;
    return &s;
}

std::vector<DataStorage>& Storage::data()
{
    return store;
}

Options& Storage::options()
{
    return _settings;
}

void Storage::sort()
{
    std::sort(store.begin(),store.end(),[](const auto& e1, const auto&e2)
    {
        if (e1.at(MODULE_NUM) == e2.at(MODULE_NUM))
        {
            if (e1.genericType() == e2.genericType())
                return e1.at(PART_N) < e2.at(PART_N);
            else
                return e1.genericType() > e2.genericType();
        }
        else return e1.at(MODULE_NUM) < e2.at(MODULE_NUM);
    });
}

Configuration& Storage::cfg()
{
    return conf;
}


void Storage::calcRom()
{
    auto addr = conf.BaseRomAddr();
    for (auto it = store.begin(); it != store.end(); it++)
    {
        //если размер файла превышает максимальный размер сектора
        if (it->fileSize() < _settings.max_rom_section_size)
        {
            it->setRomAddr(addr);
            addr+=_settings.max_rom_section_size;
        }
        else
        {
            emit sectionError("Файл " + it->genericName() + " больше максимально заданного размера");
            return;
        }
    }
    emit sectionError("");
}


