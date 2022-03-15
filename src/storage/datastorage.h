#pragma once

#include <QString>
#include <QVariant>
#include <QDate>
#include <QDir>
#include <QFileInfo>
#include "tablerowprop.h"
#include <algorithm>

enum class BlockType
{
    undef,
    bis,
    bgs,
    bcvm
};

enum
{
    CFG_NAME = 1,
    COMLINE_ROM = 3,
    OUTPUT = 5
};

class DataStorage
{
    bool    isChecked{true};
    size_t  m_num{0};
    QString f_path{};
    QDate   date{QDate::currentDate()};
    size_t  version{0};
    size_t  revision{0};
    size_t  crc{0};
    QString description{};
    size_t  ram_addr{0};
    size_t  n_part{0};
    size_t  generic_size{0};
    QString generic_name{};
    size_t  rom_addr{0};
public:
    DataStorage() = default;
    ~DataStorage() = default;
    QVariant at(const int &column);
    QVariant at(const int &column) const;
    void     set(const QVariant &v, int column);
    bool     isValid(const int& column);
    static QString  name(const int &column);
    QString genericName();
    size_t  fileSize();
    size_t  fileSize() const;
    QString genericIniSize();
    size_t  genericType();
    QString genericName() const;
    QString genericIniSize() const;
    size_t  genericType() const;
    size_t  romAddr();
    size_t  romAddr() const;
    void    setRomAddr(const size_t& _addr);
private:
    QFileInfo info;
};

struct Settings
{
    size_t      rom_addr{0};
    size_t      max_rom_section_size{0x40000};
    BlockType   type{BlockType::undef};
    QString     loadpath{QDir::currentPath()};
    QString     kernelpath{QDir::currentPath()};
    QString     ramswtxtname{};
    QString     romswtxtname{};
    QString     ramrstxtname{};
    QString     romrstxtname{};
    QString     kernelflashstr{};
    QString     cfgstr{};
    bool        ramSW_enabled{false};
    bool        romSW_enabled{false};
    bool        romRS232_enabled{false};
    bool        romKernelsFpo_enabled{false};
    bool        kernel_enabled{false};
    QStringList commandHeader{{QDir::currentPath()+"/Tools4x/bin/mipsel-elf32-gcc.exe -g -c -O0 -EL -o cfg_files.o "},
                              {},   //what a cfg block name
                              {" && " + QDir::currentPath()+"/Tools4x/bin/mipsel-elf32-ld.exe -d -g -EL -T "},
                              {},   //what a comline rom
                              {" && copy cfg_files.mot "},
                              {} //where

    };
    QStringList header;
    QString file_header ="\t\t\t\t\t/*WARNING !!! -> THIS FILE IS GENERATED AUTOMATICALLY. DO NOT EDIT THIS FILE MANUALLY <- WARNING !!!*/\r\n\r\n \
typedef struct{\r\n\
    unsigned short GA;\r\n\
    unsigned short LA;\r\n\
    unsigned long kernel_addr_rom;\r\n\
    unsigned long kernel_addr_ram;\r\n\
    unsigned long kernel_size;\r\n\
    unsigned long config_addr_rom;\r\n\
    unsigned long config_addr_ram;\r\n\
    unsigned long config_size;\r\n\
    unsigned long part1_addr_rom;\r\n\
    unsigned long part1_addr_ram;\r\n\
    unsigned long part1_size;\r\n\
    unsigned long part2_addr_rom;\r\n\
    unsigned long part2_addr_ram;\r\n\
    unsigned long part2_size;\r\n\
    unsigned long part3_addr_rom;\r\n\
    unsigned long part3_addr_ram;\r\n\
    unsigned long part3_size;\r\n\
}SoftLoad;\r\n\r\n\r\n\
const SoftLoad conf_info[]  =\r\n\
{\r\n\t\
/*module           --------  kernel ---------------    ---------- config --------------    ------------ app 1 -------------    ------------ app 2 -------------    ------------ app 3 ------------- */\r\n";
    void init(const BlockType& _type)
    {
        type = _type;
        switch(type)
        {
        case BlockType::bis:
            header.push_back("1 1 25 a0040000 ");
            header.push_back("10 1 49 a0040000");
            ramrstxtname               = loadpath + "/rs_load_bis_ram.txt";
            romrstxtname               = loadpath + "/rs_load_bis_rom.txt";
            ramswtxtname               = loadpath + "/sw_load_bis_ram.txt";
            romswtxtname               = loadpath + "/sw_load_bis_rom.txt";
            commandHeader[OUTPUT]      = '"' + loadpath + "/cfg_bis.mot"  + '"';
            commandHeader[CFG_NAME]    = loadpath + "/cfg_bis.c";
            commandHeader[COMLINE_ROM] = "bis_comline_rom.cmd";
            rom_addr = 0xb0200000;
            kernelflashstr =         "1  1 25 a0040000 f 0ffc0000 " + kernelpath + "/kernel_BIS_MV100_02_02_sum.mot\r\n"\
                                     "1  1 25 a0040000 f 10040000 " + kernelpath + "/kernel_BIS_MV100_01_sum.mot\r\n"\
                                     "1  1 25 a0040000 f 100c0000 " + kernelpath + "/kernel_BIS_MV101_01_sum.mot\r\n"\
                                     "1  1 25 a0040000 0 0ffc0000 " + kernelpath + "/kernel_BIS_MV100_02_02_sum.mot\r\n"\
                                     "1  1 25 a0040000 0 10040000 " + kernelpath + "/kernel_BIS_MV100_01_sum.mot\r\n"\
                                     "1  1 25 a0040000 0 100c0000 " + kernelpath + "/kernel_BIS_MV101_01_sum.mot\r\n"\
                                     "10 1 49 a0040000 f 0ffc0000 " + kernelpath + "/kernel_BIS_MV100_02_02_sum.mot\r\n"\
                                     "10 1 49 a0040000 f 10040000 " + kernelpath + "/kernel_BIS_MV100_01_sum.mot\r\n"\
                                     "10 1 49 a0040000 f 100c0000 " + kernelpath + "/kernel_BIS_MV101_01_sum.mot\r\n"\
                                     "10 1 49 a0040000 0 0ffc0000 " + kernelpath + "/kernel_BIS_MV100_02_02_sum.mot\r\n"\
                                     "10 1 49 a0040000 0 10040000 " + kernelpath + "/kernel_BIS_MV100_01_sum.mot\r\n"\
                                     "10 1 49 a0040000 0 100c0000 " + kernelpath + "/kernel_BIS_MV101_01_sum.mot\r\n";

            cfgstr =                 "1 1 25 a0040000  f 00000000 " + loadpath   + "/cfg_bis.mot\r\n"\
                                     "1 1 25 a0040000  0 00000000 " + loadpath   + "/cfg_bis.mot\r\n"\
                                     "10 1 49 a0040000 f 00000000 " + loadpath   + "/cfg_bis.mot\r\n"\
                                     "10 1 49 a0040000 0 00000000 " + loadpath   + "/cfg_bis.mot\r\n";
            break;
        case BlockType::bcvm:
            ramrstxtname               = loadpath + "/rs_load_bcvm_ram.txt";
            romrstxtname               = loadpath + "/rs_load_bcvm_rom.txt";
            ramswtxtname               = loadpath + "/sw_load_bcvm_ram.txt";
            romswtxtname               = loadpath + "/sw_load_bcvm_rom.txt";
            commandHeader[CFG_NAME]    = loadpath + "/cfg_bcvm.c";
            commandHeader[COMLINE_ROM] = "bis_comline_rom.cmd";
            commandHeader[OUTPUT]      = '"' + loadpath + "/cfg_bcvm.mot" + '"';
            header.push_back("1 1 25 a0040000");
            header.push_back("10 1 49 a0040000");
            rom_addr = 0xb0200000;
            kernelflashstr =         "1  1 25 a0040000 f 0ffc0000 " +kernelpath + "/kernel_BCVM_MV100_02_sum.mot\r\n"\
                                     "1  1 25 a0040000 f 10040000 " +kernelpath + "/kernel_BCVM_MV100_01_sum.mot\r\n"\
                                     "1  1 25 a0040000 f 100c0000 " +kernelpath + "/kernel_BCVM_MV101_01_sum.mot\r\n"\
                                     "1  1 25 a0040000 f 10140000 " +kernelpath + "/kernel_BCVM_MV102_01_sum.mot\r\n"\
                                     "1  1 25 a0040000 0 0ffc0000 " +kernelpath + "/kernel_BCVM_MV100_02_sum.mot\r\n"\
                                     "1  1 25 a0040000 0 10040000 " +kernelpath + "/kernel_BCVM_MV100_01_sum.mot\r\n"\
                                     "1  1 25 a0040000 0 100c0000 " +kernelpath + "/kernel_BCVM_MV101_01_sum.mot\r\n"\
                                     "1  1 25 a0040000 0 10140000 " +kernelpath + "/kernel_BCVM_MV102_01_sum.mot\r\n"\
                                     "10 1 49 a0040000 f 0ffc0000 " +kernelpath + "/kernel_BCVM_MV100_02_sum.mot\r\n"\
                                     "10 1 49 a0040000 f 10040000 " +kernelpath + "/kernel_BCVM_MV100_01_sum.mot\r\n"\
                                     "10 1 49 a0040000 f 100c0000 " +kernelpath + "/kernel_BCVM_MV101_01_sum.mot\r\n"\
                                     "10 1 49 a0040000 f 10140000 " +kernelpath + "/kernel_BCVM_MV102_01_sum.mot\r\n"\
                                     "10 1 49 a0040000 0 0ffc0000 " +kernelpath + "/kernel_BCVM_MV100_02_sum.mot\r\n"\
                                     "10 1 49 a0040000 0 10040000 " +kernelpath + "/kernel_BCVM_MV100_01_sum.mot\r\n"\
                                     "10 1 49 a0040000 0 100c0000 " +kernelpath + "/kernel_BCVM_MV101_01_sum.mot\r\n"\
                                     "10 1 49 a0040000 0 10140000 " +kernelpath + "/kernel_BCVM_MV102_01_sum.mot\r\n";

            cfgstr =                 "1  1 25 a0040000 f 00000000 " +loadpath   + "/cfg_bcvm.mot\r\n"\
                                     "1  1 25 a0040000 0 00000000 " +loadpath   + "/cfg_bcvm.mot\r\n"\
                                     "10 1 49 a0040000 f 00000000 " +loadpath   + "/cfg_bcvm.mot\r\n"\
                                     "10 1 49 a0040000 0 00000000 " +loadpath   + "/cfg_bcvm.mot\r\n";
            break;
        case BlockType::bgs:
            ramrstxtname               = loadpath + "/rs_load_bgs_ram.txt";
            romrstxtname               = loadpath + "/rs_load_bgs_rom.txt";
            ramswtxtname               = loadpath + "/sw_load_bgs_ram.txt";
            romswtxtname               = loadpath + "/sw_load_bgs_rom.txt";
            commandHeader[OUTPUT]      = '"' + loadpath + "/cfg_bgs.mot" + '"';
            commandHeader[CFG_NAME]    = loadpath + "/cfg_bgs.c";
            commandHeader[COMLINE_ROM] = "bgs_comline_rom.cmd";
            header.push_back("1 1 25 a0040000");
            header.push_back("1 2 26 a0040000");
            rom_addr = 0xbc200000;

            kernelflashstr =         "1 1 25 a0040000 f 1bfc0000 " + kernelpath +"/kernel_BGS_MV102_02_01_sum.mot\r\n"\
                                     "1 1 25 a0040000 f 1c7c0000 " + kernelpath + "/kernel_BGS_MG100_pzuELF_sum.mot\r\n"\
                                     "1 1 25 a0040000 f 1c0c0000 " + kernelpath + "/kernel_BGS_MV101_01_sum.mot\r\n"\
                                     "1 1 25 a0040000 0 1bfc0000 " + kernelpath + "/kernel_BGS_MV102_02_01_sum.mot\r\n"\
                                     "1 1 25 a0040000 0 1c7c0000 " + kernelpath + "/kernel_BGS_MG100_pzuELF_sum.mot\r\n"\
                                     "1 1 25 a0040000 0 1c0c0000 " + kernelpath + "/kernel_BGS_MV101_01_sum.mot\r\n"\
                                     "1 2 26 a0040000 f 1bfc0000 " + kernelpath + "/kernel_BGS_MV102_02_01_sum.mot\r\n"\
                                     "1 2 26 a0040000 f 1c7c0000 " + kernelpath + "/kernel_BGS_MG100_pzuELF_sum.mot\r\n"\
                                     "1 2 26 a0040000 f 1c0c0000 " + kernelpath + "/kernel_BGS_MV101_01_sum.mot\r\n"\
                                     "1 2 26 a0040000 0 1bfc0000 " + kernelpath + "/kernel_BGS_MV102_02_01_sum.mot\r\n"\
                                     "1 2 26 a0040000 0 1c7c0000 " + kernelpath + "/kernel_BGS_MG100_pzuELF_sum.mot\r\n"\
                                     "1 2 26 a0040000 0 1c0c0000 " + kernelpath + "/kernel_BGS_MV101_01_sum.mot\r\n"\
                                     "1 1 25 a0040000 f 3c6c0000 " + kernelpath + "/WorkSW_mk100.sre\r\n"\
                                     "1 1 25 a0040000 0 3c6c0000 " + kernelpath + "/WorkSW_mk100.sre\r\n"\
                                     "1 1 26 a0040000 f 3c6c0000 " + kernelpath + "/WorkSW_mk100.sre\r\n"\
                                     "1 1 26 a0040000 0 3c6c0000 " + kernelpath + "/WorkSW_mk100.sre\r\n";

            cfgstr =                 "1 1 25 a0040000 f 00000000 " + loadpath   + "/cfg_bgs.mot\r\n"\
                                     "1 1 25 a0040000 0 00000000 " + loadpath   + "/cfg_bgs.mot\r\n"\
                                     "1 2 26 a0040000 f 00000000 " + loadpath   + "/cfg_bgs.mot\r\n"\
                                     "1 2 26 a0040000 0 00000000 " + loadpath   + "/cfg_bgs.mot\r\n";
            break;
        case BlockType::undef:
            ramrstxtname.clear();
            romrstxtname.clear();
            ramswtxtname.clear();
            romswtxtname.clear();
            commandHeader[OUTPUT].clear();
            commandHeader[CFG_NAME].clear();
            commandHeader[COMLINE_ROM].clear();
            header.clear();
            kernelflashstr.clear();
            cfgstr.clear();
            rom_addr = 0;
            break;
        }
    }
};


class Storage : public QObject
{
    Q_OBJECT
public:
    static Storage* load()
    {
        static Storage s;
        return &s;
    }
    std::vector<DataStorage>& data()
    {
        return store;
    }
    Settings& settings()
    {
        return _settings;
    }
signals:
    void sectionError(const QString& what);
public slots:
    void sort()
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
    void calcRom()
    {
        auto addr = _settings.rom_addr;
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
private:
    Storage() {}
    Storage(const Storage&) = delete;
    Storage& operator=(const Storage&) = delete;
    std::vector<DataStorage> store;
    Settings _settings;
};
