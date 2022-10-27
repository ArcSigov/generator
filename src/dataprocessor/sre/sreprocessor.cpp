#include "sreprocessor.h"
#include <string>
#include <QTextCodec>


SreProcessor::SreProcessor(QObject *parent, const RecType& _record_type) : DataProcessor(parent),type(_record_type)
{
    switch (type)
    {
    case RecType::S1:
        rec_size = 16; header = "S1"; break;
    case RecType::S2:
        rec_size = 24; header = "S2"; break;
    case RecType::S3:
        rec_size = 32; header = "S3"; break;
    default: break;
    }
}

/*!
Выполняет запись бинарных данных в файл в формате S-Record
\param[in] bynarydata путь к бинарному файлу
*/
void SreProcessor::process()
{
    for (const auto& it : Storage::load()->data())
    {
        if (it.at(IS_CHECKED).toBool())
        {
            QStringList srec;
            QByteArrayList memory;
            if (!it.genericType())
            {
                memory = manager->read(rec_size,it.at(FILE_PATH).toString());
                if(memory.last().size() == 32) memory.push_back(0);
                write_sre(0,memory,srec);
            }
            else
            {
                srec = manager->read(nullptr,it.at(FILE_PATH).toString());
                for (auto& it: srec) it.push_back("\r\n");
                srec.pop_back();
                memory = read_sre(srec);
            }

            auto crc = 0u;
            auto id_mem = make_id(it);
            calc_checksumm(crc,id_mem+memory);
            memcpy(id_mem.last().begin()+12,&crc,4);
            write_sre(it.fileSize()-sizeof(ID_PO_TYPE), id_mem,srec);

            srec.push_back(terminate_str);
            if (it.genericType()) srec.push_back("\r\n");

            manager->setFilePath(Storage::load()->options().loadpath + "/"+it.genericName());
            manager->write(srec);
        }
    }
}

/*!
Выполняет запись бинарных данных elf.файла в файл в формате S-Record
\param[in] data данные и идентификационные признаки файла
*/
void SreProcessor::write_sre(size_t base_addr,const QByteArrayList &data, QStringList& out)
{
    //!< выполняем чтение файла в виде массива байтs
    unsigned char checksumm = 0;
    unsigned char* p_base_addr = (unsigned char*)&base_addr;

    //!< проход по загруженному файлу
    for (const auto& mem : data)
    {
        //!< подсчитываем количество записываемых данных (количество байт +  байт контрольной суммы + х байт записи в зависимости от типа
        auto count  = mem.size() + rec_size / 8 + 1;
        checksumm  += count + p_base_addr[0] + p_base_addr[1] + p_base_addr[2] + p_base_addr[3];
        auto str = header+QString::number(count,16).rightJustified(2,'0').toUpper()+QString::number(base_addr,16).rightJustified(8,'0').toUpper();

        for (const auto& byte : mem)
        {
            checksumm += byte;
            str+=QString::number(static_cast<unsigned char>(byte),16).rightJustified(2,'0').toUpper();
        }
        str+=QString::number(0xff-checksumm,16).toUpper().rightJustified(2,'0') + "\r\n";

        //!< осуществляем проход памяти массива байтов
        base_addr += mem.size();
        checksumm = 0;
        out.push_back(str);
    }
}


/*!
Выполняет модификацию S-record файла с внесением в него идентификационных признаков
\param[in] data данные и идентификационные признаки файла
*/
void SreProcessor::create_cfg()
{

}

/*!
Выполняет запись идентификационных признаков в бинарное представление
\param[in] data идентификационные признаки файла
*/
QByteArrayList SreProcessor::make_id(const DataStorage& data)
{
    QTextCodec* codec = QTextCodec::codecForName("CP1251");
    QByteArrayList out;
    ID_PO_TYPE id;
    memset(&id,0,sizeof(ID_PO_TYPE));

    auto name = codec->fromUnicode(data.at(DESCRIPTION).toString());
    auto date = codec->fromUnicode(data.at(ID_DATE).toDate().toString(Qt::SystemLocaleShortDate));

    id.ver = data.at(REVISION).toUInt();
    id.red = data.at(VERSION).toUInt();
    memset(id.identity,' ',36);
    memset(id.date,' ',12);
    memset(id.name,' ',24);
    memcpy(id.date,date.data(),date.size());
    memcpy(id.name,name.data(),name.size());


    out.push_back(QByteArray((char*)&id,32));
    out.push_back(QByteArray((char*)&id+32,32));
    out.push_back(QByteArray((char*)&id+64,16));

    return out;
}



QByteArrayList SreProcessor::read_sre(const QStringList& srec)
{
    QByteArrayList out;
    for (const auto& it : srec)
    {
        if (it.contains("S3"))
        {
            QByteArray srec_str;
            auto bytes_count = QString(it.data()+2,2).toUInt(nullptr,16) -1 - 4;
            auto pos = 12;
            for (auto i = 0ull; i < bytes_count;i++)
            {
                srec_str.push_back(QString(it.data()+pos,2).toUInt(nullptr,16));
                pos+=2;
            }
            out.push_back(srec_str);
        }
    }
    return out;
}

struct bitfield_t
{
    unsigned int hi;
    unsigned int lo;
};

void SreProcessor::calc_checksumm(unsigned int& crc, QByteArrayList memory)
{
    bitfield_t b;
    bitfield_t t;
    memset(&b,0,8);
    memset(&t,0,8);
    memcpy(&b,&crc,4);
    for (auto& mem : memory)
    {
        while (mem.size() % 4 != 0)
        {
            mem.insert(mem.size()-1,1,0);
        }


        for (auto pos = 0ull; pos < mem.size(); pos +=4)
        {
            size_t value = 0;
            memcpy(&value,mem.data()+pos,4);

            *(size_t*)&b += value;
//            while (b.hi)
//            {
//                b.lo +=b.hi;
//                b.hi = 0;
//            }
        }
    }

    *(size_t*)&t = (size_t)b.lo + (size_t)b.hi;
    crc = t.lo + t.hi;
}
