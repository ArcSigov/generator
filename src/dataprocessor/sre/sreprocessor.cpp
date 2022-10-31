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
    for (auto& it : Storage::load()->data())
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

            auto crc         = 0u;
            auto table_crc   = it.at(CRC).toUInt();
            auto id_mem      = make_id(it);
            auto offset_size = 0u;
            calc_checksumm(crc,id_mem+memory);

            //если табличная КС введена и она не равна рассчитанной
            if (table_crc > 0 && table_crc != crc)
            {
                offset_size = 4u;
                remake_id(id_mem,(table_crc - crc) - (crc > table_crc ? 1 : 0),table_crc);
            }
            // иначе просто записать контрольную сумму в идентификационные признаки
            else
            {
                 it.set(crc,CRC);
                 memcpy(id_mem.last().begin()+12,&crc,4);
            }


            write_sre(it.fileSize()-sizeof(ID_PO_TYPE) - offset_size, id_mem,srec);
            srec.push_back(terminate_str);
            if (it.genericType()) srec.push_back("\r\n");

            manager->setFilePath(Storage::load()->options().loadpath + "/"+it.genericName());
            manager->write(srec);

            emit sendMessage(MessageCategory::update,"Генерация файла " + it.genericName() + " завершена");
        }
    }
}

/*!
Выполняет запись бинарных данных файла в файл в формате S-Record
\param[in] data данные и идентификационные признаки файла
*/
void SreProcessor::write_sre(size_t base_addr,const QByteArrayList &data, QStringList& out)
{
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

        base_addr += mem.size();
        checksumm = 0;
        out << str;
    }
}

/*!
Выполняет запись идентификационных признаков в бинарное представление
\param[in] data идентификационные признаки файла
\param[out] массив идентификационных признаков
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


/*!
Выполняет чтение s record формата в бинарное представление
\param[in] srec загрузочный файл
\param[out] бинарные данные файла
*/
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

/*!
Выполняет расчёт контрольной суммы бинарных данных
\param[in] crc данные для хранения контрольной суммы
\param[in] memory бинарные данные файла
*/
void SreProcessor::calc_checksumm(unsigned int& crc, QByteArrayList memory)
{
    bitfield_t b;
    bitfield_t t;
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
        }
    }
    *(size_t*)&t = (size_t)b.lo + (size_t)b.hi;
    crc = (t.lo+t.hi);
}


void SreProcessor::remake_id(QByteArrayList& id, const size_t& res, const size_t& crc)
{
    QByteArray memory;
    if (id.size() == 3)
    {
        memory.push_back(id[0]);
        memory.push_back(id[1]);
        memory.push_back(id[2]);
        memory.insert(0,(char*)&res,4);
        memcpy(memory.begin()+80,&crc,4);

        id.clear();
        id.push_back(QByteArray(memory.data(),32));
        id.push_back(QByteArray(memory.data()+32,32));
        id.push_back(QByteArray(memory.data()+64,20));
    }
}
