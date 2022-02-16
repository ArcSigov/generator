#include "cfgprocessor.h"
#include "tablerowprop.h"

CfgDataProcessor::CfgDataProcessor() : block (std::make_unique<BlockCfg>())
{

}

/*!
Выполняет генерацию конфигурационного блока для выбранного блока
*/
void CfgDataProcessor::process()
{
    if (!storage) return;

    QStringList str(file_header);
    block->clear();

    for (auto it = storage->begin(); it != storage->end(); it++)
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

    if (manager)
    {
        manager->setFilePath(outcfgname);
        manager->write(str);
    }
}

/*!
Устанавливает процессору генерации cfg файлов путь для сохранения сгенерированного конфигурационного файла и инициализирует объект шаблона конфигурационного файла
\param[in] &_settings ссылка на настройки программы
*/
void CfgDataProcessor::update()
{
    if (settings)
    {
        switch (settings->type)
        {
        case BlockType::bis:
            outcfgname = settings->abspath+"/cfg_bis.c";
            block = std::make_unique<BisCfg>();
            break;
        case BlockType::bcvm:
            outcfgname = settings->abspath+"/cfg_bcvm.c";
            block = std::make_unique<BcvmCfg>();
            break;
        case BlockType::bgs:
            outcfgname = settings->abspath+"/cfg_bgs.c";
            block = std::make_unique<BgsCfg>();
            break;
        case BlockType::undef:
            block = std::make_unique<BlockCfg>();
            break;
        default:break;
        }
    }
}
