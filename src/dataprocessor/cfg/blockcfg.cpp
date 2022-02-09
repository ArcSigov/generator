#include "blockcfg.h"

BisCfg::BisCfg()
{
    blockcfg.emplace_back(0x0001,0x0025,0xb0000000);
    blockcfg.emplace_back(0x0002,0x0029,0xb0080000);
    blockcfg.emplace_back(0x0003,0x002d,0xb0100000);
    blockcfg.emplace_back(0x0004,0x0031,0xb0100000);
    blockcfg.emplace_back(0x0005,0x0035,0xb0100000);
    blockcfg.emplace_back(0x0006,0x0039,0xb0100000);
    blockcfg.emplace_back(0x0007,0x003d,0xb0100000);
    blockcfg.emplace_back(0x0008,0x0041,0xb0100000);
    blockcfg.emplace_back(0x0009,0x0045,0xb0080000);
    blockcfg.emplace_back(0x000A,0x0049,0xb0000000);
}

BcvmCfg::BcvmCfg()
{
    blockcfg.emplace_back(0x0001,0x0025,0xb0000000);
    blockcfg.emplace_back(0x0002,0x0029,0xb0180000);
    blockcfg.emplace_back(0x0002,0x002a,0xb0180000);
    blockcfg.emplace_back(0x0003,0x002d,0xb0080000);
    blockcfg.emplace_back(0x0004,0x0031,0xb0080000);
    blockcfg.emplace_back(0x0005,0x0035,0xb0100000);
    blockcfg.emplace_back(0x0006,0x0039,0xb0100000);
    blockcfg.emplace_back(0x0007,0x003d,0xb0100000);
    blockcfg.emplace_back(0x0008,0x0041,0xb0080000);
    blockcfg.emplace_back(0x0009,0x0045,0xb0080000);
    blockcfg.emplace_back(0x000A,0x0049,0xb0000000);
}

BgsCfg::BgsCfg()
{
    blockcfg.emplace_back(0x0001,0x0025,0xbc000000);
    blockcfg.emplace_back(0x0001,0x0026,0xbc000000);
    blockcfg.emplace_back(0x0002,0x0029,0xbc700000);
    blockcfg.emplace_back(0x0003,0x002d,0xbc800000);
    blockcfg.emplace_back(0x0003,0x002e,0xbc800000);
    blockcfg.emplace_back(0x0004,0x0031,0xbc800000);
    blockcfg.emplace_back(0x0004,0x0032,0xbc800000);
    blockcfg.emplace_back(0x0005,0x0035,0xbc800000);
    blockcfg.emplace_back(0x0005,0x0036,0xbc800000);
    blockcfg.emplace_back(0x0006,0x0039,0xbc800000);
    blockcfg.emplace_back(0x0006,0x003a,0xbc800000);
    blockcfg.emplace_back(0x0007,0x003d,0xbc800000);
    blockcfg.emplace_back(0x0007,0x003e,0xbc800000);
    blockcfg.emplace_back(0x0008,0x0041,0xbc800000);
    blockcfg.emplace_back(0x0008,0x0042,0xbc800000);
    blockcfg.emplace_back(0x0009,0x0045,0xbc700000);
    blockcfg.emplace_back(0x000A,0x0049,0xbc100000);

    blockcfg[2].kernel_size = 0x20000;
    blockcfg[15].kernel_size = 0x20000;
}

void BlockCfg::insert (const size_t& LA, const size_t& ram_addr, const size_t& rom_addr, const size_t& size, const size_t& npart)
{
    for (auto it = blockcfg.begin(); it!= blockcfg.end(); it++)
    {
        if (it->LA == LA)
        {
            it->part_addr_ram[npart] = ram_addr;
            it->part_addr_rom[npart] = rom_addr;
            it->part_size[npart]     = size;
        }
    }
}

size_t BlockCfg::size()
{
    return blockcfg.size();
}

SoftLoad& BlockCfg::operator[] (const size_t& pos)
{
    return blockcfg[pos];
}
SoftLoad& BlockCfg::at(const size_t& pos)
{
    return blockcfg[pos];
}
const SoftLoad& BlockCfg::at(const size_t& pos) const
{
    return blockcfg[pos];
}

void BlockCfg::clear()
{
    for (auto it : blockcfg)
    {
        for (auto i = 0 ; i < 4 ; i++)
        {
            it.part_addr_ram[i] = 0xffffffff;
            it.part_addr_rom[i] = 0xffffffff;
            it.part_size[i]     = 0xffffffff;
        }
    }
}

