#include "cfggenerator.h"

BaseCfgGen::BaseCfgGen(const QString& _outdir, const QString& blockname )
{

}

BaseCfgGen::~BaseCfgGen()
{

}

void BaseCfgGen::SetOutputDir(const QString& outdir)
{

}

void BaseCfgGen::Add        (const QString& file_path, const QString& la,
                             const QString& ram_addr,  const L_FILE& type,
                             const size_t& file_size,  const size_t& part_num)
{

    NextSector(file_size);
}

void BaseCfgGen::WriteToTable()
{

}

void BaseCfgGen::MakeStr(QString &str, const size_t &val, const size_t &null_count)
{
}
void BaseCfgGen::WriteToSwFile(const QString& file)
{
    sw_txt_file.write(QString("1 1 25 a0040000 f " + file + "\r\n").toStdString().c_str());
    sw_txt_file.write(QString("1 1 25 a0040000 0 " + file + "\r\n").toStdString().c_str());
    sw_txt_file.write(QString("10 1 49 a0040000 f " + file + "\r\n").toStdString().c_str());
    sw_txt_file.write(QString("10 1 49 a0040000 0 " + file + "\r\n").toStdString().c_str());
}

void BaseCfgGen::WriteToRsFile(const QString &file_name)
{
    rs_data.push_back(QString::number(rs_position++) + " 0 " + file_name + "\r\n");
}

void BaseCfgGen::NextSector(const size_t& file_size)
{
    if (file_size < 0x40000)
    {
        base_rom_addr+=0x40000;
    }
    else
    {
        int _size = file_size;
        while (_size > 0)
        {
            base_rom_addr+=0x40000;
            _size-=0x40000;
        }
    }
}

void BaseCfgGen::WriteToCfg(const size_t& module_num,const QString& ram_addr,const size_t& size)
{
    table[module_num].config_addr_ram = "0x"+ram_addr;
    table[module_num].config_addr_rom = "0x"+QString::number(base_rom_addr,16);
    MakeStr(table[module_num].config_size,size,8);
}

void BaseCfgGen::WriteToPart(const size_t& module_num,const size_t& part_num,const QString& ram_addr,const size_t& size)
{
    table[module_num].part_addr_ram[part_num-1] = "0x"+ram_addr;
    table[module_num].part_addr_rom[part_num-1] = "0x"+QString::number(base_rom_addr,16);
    MakeStr(table[module_num].part_size[part_num-1],size,8);
}

void BaseCfgGen::RunBatch()
{
    QDir dir;
    dir.mkpath("out/cfg/obj");
    QFile batch("out/cfg/make_"+QFileInfo(cfg_file).baseName()+".bat");
    if (batch.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        QTextStream stream(&batch);
        stream << QDir::currentPath() << "/Tools4x/bin/mipsel-elf32-gcc.exe -g -c -O0 -EL  -o " << QDir::currentPath()+"/out/cfg/obj/" << "cfg_files.o "  + QFileInfo(cfg_file).absoluteFilePath() + "\r\n";
        stream << "cd " << QDir::currentPath()+"/out/cfg/obj" << "\r\n";
        stream << QDir::currentPath() << "/Tools4x/bin/mipsel-elf32-ld.exe  -d  -g -EL -T " << QDir::currentPath() <<  (QFileInfo(cfg_file).baseName() == "cfg_bgs" ? "/bgs_comline_rom.cmd" : "/comline_rom.cmd") << "\r\n";
        stream << "copy cfg_files.mot " << '"' << outdir + QFileInfo(cfg_file).baseName() + ".mot" << '"' << "\r\n";
    }
    batch.close();
    std::system(("cmd.exe /C " + QDir::currentPath().toStdString() + "/out/cfg/make_" + QFileInfo(cfg_file).baseName().toStdString() + ".bat").c_str());
}

BisCfgGen::BisCfgGen(const QString& outdir) : BaseCfgGen(outdir,"bis")
{
    base_rom_addr = 0xb0200000;

}

#include <iostream>

BisCfgGen::~BisCfgGen()
{
    sw_txt_file.write(QString("1 1 25 a0040000 f 00000000 " +load_outdir+"cfg_bis.mot\r\n").toStdString().c_str());
    sw_txt_file.write(QString("1 1 25 a0040000 0 00000000 " +load_outdir+"cfg_bis.mot\r\n").toStdString().c_str());
    sw_txt_file.write(QString("10 1 49 a0040000 f 00000000 " +load_outdir+"cfg_bis.mot\r\n").toStdString().c_str());
    sw_txt_file.write(QString("10 1 49 a0040000 0 00000000 " +load_outdir+"cfg_bis.mot\r\n").toStdString().c_str());

    rs_data.push_front("0 f b0200000-" + QString::number(base_rom_addr,16)+"\r\n");
    rs_data.push_back(QString::number(rs_position++) + " f b7f80000\r\n");
    rs_data.push_back(QString::number(rs_position++) + " 0 00000000 "+ load_outdir + "cfg_bis.mot\r\n");
    rs_txt_file.write(rs_data.toStdString().c_str());
}

BcvmCfgGen::BcvmCfgGen(const QString& outdir) : BaseCfgGen(outdir,"bcvm")
{
    base_rom_addr = 0xb0200000;

}

BcvmCfgGen::~BcvmCfgGen()
{
    sw_txt_file.write(QString("1 1 25 a0040000 f 00000000 " +load_outdir+"cfg_bcvm.mot\r\n").toStdString().c_str());
    sw_txt_file.write(QString("1 1 25 a0040000 0 00000000 " +load_outdir+"cfg_bcvm.mot\r\n").toStdString().c_str());
    sw_txt_file.write(QString("10 1 49 a0040000 f 00000000 " +load_outdir+"cfg_bcvm.mot\r\n").toStdString().c_str());
    sw_txt_file.write(QString("10 1 49 a0040000 0 00000000 " +load_outdir+"cfg_bcvm.mot\r\n").toStdString().c_str());

    rs_data.push_front("0 f b0200000-" + QString::number(base_rom_addr,16)+"\r\n");
    rs_data.push_back(QString::number(rs_position++) + " f b7f80000\r\n");
    rs_data.push_back(QString::number(rs_position++) + " 0 00000000 "+ load_outdir + "cfg_bcvm.mot\r\n");
    rs_txt_file.write(rs_data.toStdString().c_str());
}

BgsCfgGen::BgsCfgGen(const QString& outdir) : BaseCfgGen(outdir,"bgs")
{
    base_rom_addr = 0xbc200000;

}
BgsCfgGen::~BgsCfgGen()
{

    sw_txt_file.write(QString("1 1 25 a0040000 f 00000000 " +load_outdir+"cfg_bgs.mot\r\n").toStdString().c_str());
    sw_txt_file.write(QString("1 2 26 a0040000 f 00000000 " +load_outdir+"cfg_bgs.mot\r\n").toStdString().c_str());
    sw_txt_file.write(QString("1 1 25 a0040000 0 00000000 " +load_outdir+"cfg_bgs.mot\r\n").toStdString().c_str());
    sw_txt_file.write(QString("1 2 26 a0040000 0 00000000 " +load_outdir+"cfg_bgs.mot\r\n").toStdString().c_str());

    rs_data.push_front("0 f bc200000-" + QString::number(base_rom_addr,16)+"\r\n");
    rs_data.push_back(QString::number(rs_position++) + " f bfc80000\r\n");
    rs_data.push_back(QString::number(rs_position++) + " 0 00000000 "+ load_outdir + "cfg_bgs.mot\r\n");
    rs_txt_file.write(rs_data.toStdString().c_str());
}

void BgsCfgGen::WriteToSwFile(const QString &file)
{
    sw_txt_file.write(QString("1 1 25 a0040000 f " + file + "\r\n").toStdString().c_str());
    sw_txt_file.write(QString("1 1 25 a0040000 0 " + file + "\r\n").toStdString().c_str());
    sw_txt_file.write(QString("1 2 26 a0040000 f " + file + "\r\n").toStdString().c_str());
    sw_txt_file.write(QString("1 2 26 a0040000 0 " + file + "\r\n").toStdString().c_str());
}


