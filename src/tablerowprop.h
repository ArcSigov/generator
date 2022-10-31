#pragma once

#include <QDir>

enum ColumnProp
{
    IS_CHECKED,
    MODULE_NUM,
    FILE_PATH,
    ID_DATE,
    VERSION,
    REVISION,
    CRC,
    DESCRIPTION,
    RAM_ADDR,
    PART_N,
    COLUMN_COUNT
};


struct Options
{
    size_t      max_rom_section_size{0x40000};
    QString     loadpath{QDir::currentPath()};
    QString     kernelpath{QDir::currentPath()};
    bool        ramSW_enabled{true};
    bool        romSW_enabled{true};
    bool        romRS232_enabled{true};
    bool        romKernelsFpo_enabled{true};
    bool        kernel_enabled{true};
};
