#pragma once

#include <vector>
#include "options.h"

struct SoftLoad
{
    unsigned short GA{0xffff};
    unsigned short LA{0xffff};
    unsigned long kernel_addr_rom{0xffffffff};
    unsigned long kernel_addr_ram{0xa0040000};
    unsigned long kernel_size{0x50000};
    unsigned long part_addr_rom[4]{0xffffffff,0xffffffff,0xffffffff,0xffffffff};
    unsigned long part_addr_ram[4]{0xa00a0000,0xffffffff,0xffffffff,0xffffffff};
    unsigned long part_size[4]{0xffffffff,0xffffffff,0xffffffff,0xffffffff};
    SoftLoad(const unsigned short& _GA,const unsigned short& _LA, const unsigned long& _kernel_addr_rom) : GA(_GA), LA(_LA), kernel_addr_rom(_kernel_addr_rom) {}
};

class BlockCfg
{
public:
    BlockCfg() = default;
    virtual ~BlockCfg() = default;
    void insert (const size_t& LA = 0, const size_t& ram_addr = 0, const size_t& rom_addr = 0, const size_t& size  = 0, const size_t& npart = 0);
    size_t size();
    SoftLoad& operator[] (const size_t& pos);
    SoftLoad& at(const size_t& pos);
    const SoftLoad& at(const size_t& pos) const;
protected:
    std::vector<SoftLoad> blockcfg;
};

class BisCfg : public BlockCfg
{
public:
    BisCfg();
    ~BisCfg() = default;
};

class BcvmCfg : public BlockCfg
{
public:
    BcvmCfg();
    ~BcvmCfg() = default;
};

class BgsCfg : public BlockCfg
{
public:
    BgsCfg();
    ~BgsCfg() = default;
};
