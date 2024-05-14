#include "sziprocessor.h"
#include "sziprocessorlocal.h"
#include "sreprocessor.h"
#include <QStringList>
#include <QDebug>


SziDataProcessor::SziDataProcessor(Manager* _sre,QObject *parent)
    : DataProcessor{parent},sre{_sre}
{

}

void SziDataProcessor::process()
{
    //!< Для блока БГС класс не работает
    if (Storage::load()->cfg().BlockName() == "BGS")
        return;

    QStringList list;
    QByteArrayList sre_list;
    list.push_back(file_header);

    //!< Парсим таблицу под формат СЗИ и формируем контейнер для загрузки в изделие
    for (const auto& data: Storage::load()->data())
    {
        auto logical_adresses = data.at(MODULE_NUM).toString().split(",");
        for (const auto& la: logical_adresses)
        {
            PO_CHECKSUM po;
            po.CHECKSUM = data.at(CRC).toUInt();
            po.NUMBER_CPU = getCpu(la.toUInt(nullptr,16));
            po.NUMBER_MODUL = Storage::load()->cfg().getLaName(la.toUInt(nullptr,16));
            po.NUMBER_PO = data.at(PART_N).toUInt()+1;
            sre_list.push_back(QByteArray(static_cast<char*>(static_cast<void*>(&po)),sizeof(PO_CHECKSUM)));
        }
    }

    //!< Парсим ядра для занесения их признаков в таблицу СЗИ
    for (auto i = 1; i < 11; i++)
    {
        auto kernel = Storage::load()->cfg().getKernel(i);
        auto kernel_data = sre->read(Storage::load()->options().kernelpath + "/" + kernel.name);
        if (kernel_data.size() > 3)
        {
            PO_CHECKSUM po;
            po.CHECKSUM = reinterpret_cast<ID_PO_TYPE*>(kernel_data.data()+kernel_data.size()-sizeof(ID_PO_TYPE))->KS;
            po.NUMBER_CPU = 1;
            po.NUMBER_MODUL = i;
            po.NUMBER_PO = 0;
            sre_list.push_back(QByteArray(static_cast<char*>(static_cast<void*>(&po)),sizeof(PO_CHECKSUM)));
            if (Storage::load()->cfg().BlockName() == "BCVM" && i == 2)
            {
                po.NUMBER_CPU = 2;
                sre_list.push_back(QByteArray(static_cast<char*>(static_cast<void*>(&po)),sizeof(PO_CHECKSUM)));
            }
        }
    }

    //!< Сортируем данные по модулю и номеру раздела в модуле
    std::sort(sre_list.begin(),sre_list.end(),[](QByteArray& first, QByteArray& next)
    {
        if (first[0] == next[0])
            return first[8] < next[8];
        return first[0] < next[0];
    });
    PO_CHECKSUM last;
    sre_list.push_back(QByteArray(static_cast<char*>(static_cast<void*>(&last)),sizeof(PO_CHECKSUM)));

    //!< Формируем .с файл для визуализации или генерации сторонним линкером
    for (auto po = sre_list.begin(); po !=sre_list.end(); po++)
    {
        auto p = static_cast<PO_CHECKSUM*>(static_cast<void*>(po->data()));
        if (po !=sre_list.begin()) list.push_back(",\r\n");
        list.push_back("\t{0x"+QString::number(p->NUMBER_MODUL,16).rightJustified(8,'0').toUpper()     + ", 0x" +
                               QString::number(p->NUMBER_CPU).rightJustified(8,'0').toUpper()       + ", 0x" +
                               QString::number(p->NUMBER_PO).rightJustified(8,'0').toUpper()        + ", " +
                               "0x"+QString::number(p->CHECKSUM,16).rightJustified(8,'0') + "}");

    }
    list.push_back("\r\n};\r\n");

    if (manager)
    {
        manager->setFilePath(Storage::load()->options().loadpath + "/szi_" + Storage::load()->cfg().BlockName() + ".c");
        manager->write(list);
    }

    auto file = "szi_" + Storage::load()->cfg().BlockName() + ".mot";
    if (sre && sre->beginWrite(Storage::load()->options().loadpath +"/"+ file))
    {
        sre->write("rec_type:S0,base_addr:0",QByteArrayList({QByteArray(file.toStdString().data(),file.length())}));
        sre->write("rec_type:S1,base_addr:0",sre_list);
        sre->endWrite();
    }
}


int SziDataProcessor::getCpu(size_t la)
{
    switch (la)
    {
        case 37:
        case 41:
        case 45:
        case 49:
        case 53:
        case 57:
        case 61:
        case 65:
        case 69:
        case 73:
            return 1;
        case 38:
        case 42:
        case 46:
        case 50:
        case 54:
        case 58:
        case 62:
        case 66:
        case 70:
        case 74:
            return 2;
        default:break;
    }
    return {};
}

