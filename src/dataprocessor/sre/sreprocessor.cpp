#include "sreprocessor.h"
#include <string>
#include <QTextCodec>
#include <iostream>

SreProcessor::SreProcessor(QObject *parent, Manager* sre) : DataProcessor(parent), sre_manager(sre)
{

}

SreProcessor::~SreProcessor(){
}
#include <QDebug>
/*!
Выполняет запись бинарных данных в файл в формате S-Record
\param[in] bynarydata путь к бинарному файлу
*/
void SreProcessor::process()
{
    for (auto& it : Storage::load()->data())
    {
        if (it.at(IS_CHECKED).toBool())
        if (sre_manager)
        {
            QByteArrayList memory;
            if (!it.genericType())
            {
                memory = manager->read(32,it.at(FILE_PATH).toString());
                if(memory.size() && memory.last().size() == 32) memory.push_back(0);
            }
            else
                memory = sre_manager->read(0ull,it.at(FILE_PATH).toString());

            if (memory.size() == 0)
            {
                emit sendMessage(MessageCategory::error,"Ошибка открытия файла: " + it.at(FILE_PATH).toString() + ", нет такого файла или каталога");
                continue;
            }


            if (sre_manager->beginWrite(Storage::load()->options().loadpath + "/" + it.genericName()))
            {
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
                sre_manager->write("rec_type:S3,base_addr:0",memory);
                sre_manager->write("rec_type:S3,base_addr:"+QString::number(it.fileSize()-sizeof(ID_PO_TYPE) - offset_size,16),id_mem);
                sre_manager->endWrite();
                emit sendMessage(MessageCategory::update,"Генерация файла " + it.genericName() + " завершена");
            }
        }
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
