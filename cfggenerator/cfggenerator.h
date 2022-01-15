#ifndef CFGGEN_H_INCLUDED
#define CFGGEN_H_INCLUDED

#include <QString>
#include <QTextStream>
#include <QFileInfo>
#include <QDir>
#include <vector>


enum class L_FILE {
    CONFIG = 0,
    BINARY
};

class BaseCfgGen{
    struct SoftLoad{
        QString  GA;
        QString  LA;
        QString kernel_addr_rom;
        QString kernel_addr_ram;
        QString kernel_size;
        QString config_addr_rom;
        QString config_addr_ram;
        QString config_size;
        QString part_addr_rom[3];
        QString part_addr_ram[3];
        QString part_size[3];
        SoftLoad(QString  _GA,
                 QString  _LA,
                 QString  _kernel_addr_rom):
                                           GA(_GA),LA(_LA),
                                           kernel_addr_rom(_kernel_addr_rom), kernel_addr_ram("0xa0040000"),kernel_size("0x00050000"),
                                           config_addr_rom("0xffffffff"),config_addr_ram("0xffffffff"),config_size("0xffffffff")
        {
            for (auto i = 0; i < 3; i++){
                part_addr_rom[i] = "0xffffffff";
                part_addr_ram[i] = "0xffffffff";
                part_size[i]     = "0xffffffff";
            }
        }
    };
public:
    virtual ~BaseCfgGen();
    void SetOutputDir(const QString& outdir);
    void Add        (const QString& file_path, const QString& la,
                     const QString& ram_addr,  const L_FILE& type,
                     const size_t& file_size,  const size_t& part_num);
    void WriteToTable();
    void RunBatch();
private:
    void MakeStr(QString& str,const size_t& val,const size_t& null_count);
    void NextSector(const size_t& file_size);
    void WriteToCfg(const size_t& module_num,const QString& ram_addr,const size_t& size);
    void WriteToPart(const size_t& module_num,const size_t& part_num,const QString& ram_addr,const size_t& size);
    virtual void WriteToSwFile(const QString& file_name);
    void WriteToRsFile(const QString& file_name);
protected:
    std::vector<SoftLoad>                 table;
    size_t                                base_rom_addr,rs_position;
    QString                               load_outdir;
    QString                               outdir;
    QString                               rs_data;
    QFile                                 cfg_file,sw_txt_file, rs_txt_file;
    BaseCfgGen(const QString& _outdir, const QString& blockname);
};

class BisCfgGen : public BaseCfgGen{
public:
    BisCfgGen(const QString& outdir);
    ~BisCfgGen();
};

class BcvmCfgGen : public BaseCfgGen{
public:
    BcvmCfgGen(const QString& outdir);
    ~BcvmCfgGen();
};

class BgsCfgGen : public BaseCfgGen{
public:
    BgsCfgGen(const QString& outdir);
    ~BgsCfgGen();
private:
    virtual void WriteToSwFile(const QString &file) override;
};

#endif
