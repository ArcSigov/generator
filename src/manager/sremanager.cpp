#include "sremanager.h"
#include <QVariant>
#include <QTextStream>
#include <QDebug>

SreManager::SreManager()
{

}

QByteArrayList SreManager::read(const size_t& block_size,const QString& path )
{
    Q_UNUSED(block_size)
    setFilePath(path);
    if (f.open(QIODevice::ReadOnly))
    {
        QByteArrayList out;
        QTextStream s(&f);
        while (!s.atEnd())
        {
            auto l = s.readLine();
            l.push_back("\r\n");
            if (l.contains("S3"))
            {
                QByteArray srec_str;
                auto bytes_count = QString(l.data()+2,2).toUInt(nullptr,16) -1 - 4;
                auto pos = 12;
                for (auto i = 0ull; i < bytes_count;i++)
                {
                    srec_str.push_back(QString(l.data()+pos,2).toUInt(nullptr,16));
                    pos+=2;
                }
                out.push_back(srec_str);
            }
        }
        f.close();
        return out;
    }
    return {};
}

bool SreManager::beginWrite(const QString& path)
{
    f.setFileName(path);
    if (f.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        return true;
    }
    return false;
}

void SreManager::endWrite()
{
    if (header == "S1" || header == "S0")      f.write("S9030000FC\r\n");
    else if (header == "S3") f.write("S70500000000FA\r\n");
    f.close();
}

void SreManager::write(const QString& options, const QByteArrayList &data)
{
    auto optionList = options.split(",");
    for (const auto& option:optionList)
    {
        if (option.contains("rec_type"))  header = option.section(':',1);
        if (option.contains("base_addr")) base_addr = option.section(':',1).toUInt(nullptr,16);
    }

    unsigned char checksumm = 0;
    unsigned char* p_base_addr = (unsigned char*)&base_addr;
    auto rec_size = header == "S2"  ? 24 : header ==  "S3" ? 32 : 16;
    auto offset = rec_size == 32 ? 8 : rec_size == 24 ? 6 : 4;
    for (const auto& mem :data)
    {
        //!< подсчитываем количество записываемых данных (количество байт +  байт контрольной суммы + х байт записи в зависимости от типа
        auto count  = mem.size() + rec_size / 8 + 1;
        checksumm   = count + p_base_addr[0] + p_base_addr[1] + p_base_addr[2] + p_base_addr[3];
        auto str = header+QString::number(count,16).rightJustified(2,'0').toUpper()+QString::number(base_addr,16).rightJustified(offset,'0').toUpper();
        for (const auto& byte : mem)
        {
            checksumm += byte;
            str+=QString::number(static_cast<unsigned char>(byte),16).rightJustified(2,'0').toUpper();
        }
        str+=QString::number(0xff-checksumm,16).toUpper().rightJustified(2,'0') + "\r\n";
        base_addr += mem.size();
        f.write(str.toStdString().c_str());
    }
}

QByteArray SreManager::read(const QString& path)
{
    return {};
}
QStringList SreManager::read(bool* ok,const QString& path)
{
    return {};
}
bool SreManager::write(const QStringList &data)
{
    return false;
}
bool SreManager::write(bool* ok,const QString &data)
{
    return false;
}
