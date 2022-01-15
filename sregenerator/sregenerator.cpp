#include "sregenerator.h"
#include "table/table.h"

SreGen::SreGen()
{
    codec = QTextCodec::codecForName("CP1251");
}

SreGen::~SreGen() { }

QString SreGen::_make_byte(QString str, int size)
{
    while (str.size() != size) str.push_front("0");
    return str;
}

void SreGen::_read_bytes(QVector<unsigned char>& v, const  QByteArray& bytes)
{
    v.clear();
    for (auto it = bytes.cbegin(); it!= bytes.cend(); it++)
    {
        v.push_back(QString::number((unsigned char)*it,10).toUInt());
    }
}

void SreGen::_write_bytes(const unsigned int& addr,unsigned char* bytes, const size_t& bytes_count, QTextStream& stream,const bool& end)
{
    auto checksumm = (addr >> 24) + (((addr)&0xff0000)>>16) + (((addr)&0xff00) >> 8) + ((addr)&0xff) + 5;
    stream << "S3" << _make_byte(QString::number(bytes_count+5,16).toUpper(),2) << _make_byte(QString::number(addr,16).toUpper(),8);
    for (auto i = 0ull ; i != bytes_count; i++)
    {
        stream << _make_byte(QString::number(*bytes,16).toUpper(),2);
        checksumm += *bytes + 1;
        bytes++;
    }
    stream << _make_byte(QString::number(0xff-(checksumm&0xff),16).toUpper(),2) << (end == true ? "\r\nS70500000000FA" : "\r\n");
}

void SreGen::calc_checksumm(unsigned int& crc,unsigned int* in,size_t count)
{
    auto summ = 0u;
    for (auto i= 0ull ; i < count; i++)
    {
        auto  t = static_cast<unsigned long long>(*in) + static_cast<unsigned long long>(summ);
        auto p = t >> 0x20;
        summ  =  static_cast<unsigned int>(t) + static_cast<unsigned int>(p);
        in++;
    }
    auto temp = static_cast<unsigned long long>(crc) + static_cast<unsigned long long>(summ);
    auto p = temp >> 0x20;
    crc  =  static_cast<unsigned int>(temp) + static_cast<unsigned int>(p);
}

void SreGen::GenerateNewSre(const QString &input_file_name, const QString &output_file_name)
{
    input.setFileName(input_file_name);
    output.setFileName(output_file_name);
    calc_checksumm(id.KS,(unsigned int*)&id.identity[0],19);
    if (output.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        if (input.open(QIODevice::ReadOnly))
        {
            auto rom_addr = 0u;
            QTextStream sre(&output);
            QVector<unsigned char> bytes;
            while (!input.atEnd())
            {
                _read_bytes(bytes,input.read(32));
                _write_bytes(rom_addr,bytes.data(),bytes.size(),sre);
                rom_addr += bytes.size();
                while (bytes.size() % 4) bytes.insert(bytes.size()-1,0);
                calc_checksumm(id.KS,(unsigned int*)bytes.data(), bytes.size()/4);
            }
            if (!(input.size() % 32)) _write_bytes(rom_addr,nullptr,0,sre);

            rom_addr = FileGen::GetNewSize(input.size()) - sizeof(ID_PO_TYPE)+4;
            _write_bytes(rom_addr,   (unsigned char*)&id.identity,   32,sre);
            _write_bytes(rom_addr+32,(unsigned char*)&id.identity+32,32,sre);
            _write_bytes(rom_addr+64,(unsigned char*)&id.identity+64,16,sre,true);

            input.close();
        }
        output.close();
    }
}

void SreGen::SetIdPO(const QString& date, const QString& version,const QString& edition, const QString& crc, const QString& description)
{
    id.clear();
    ba = codec->fromUnicode(description);
    strncpy((char*)&id.name[0],ba.data(),ba.size());
    ba = codec->fromUnicode(date);
    strncpy((char*)&id.date[0],ba.data(),ba.size());
    id.ver = std::stoi(version.toStdString());
    id.red = std::stoi(edition.toStdString());
    //auto val = strtoul(crc.toStdString().c_str(),NULL,16);
}

const auto& SreGen::GetCrc() const
{
    return id.KS;
}
