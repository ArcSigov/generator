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
    QStringList list;
    QByteArrayList sre_list;
    QByteArrayList sre_header;
    list.push_back(file_header);
    auto file = "szi_" + Storage::load()->cfg().BlockName() + ".mot";
    sre_header.push_back(QByteArray(file.toStdString().c_str(),file.size()));
    for (const auto& data: Storage::load()->data())
    {
        for (const auto& la: data.at(MODULE_NUM).toString().split(","))
        {
            PO_CHECKSUM po;
            po.CHECKSUM = data.at(CRC).toUInt();
            po.NUMBER_CPU = getCpu(la.toUInt(nullptr,16));
            po.NUMBER_MODUL = Storage::load()->cfg().getLaName(la.toUInt(nullptr,16));
            po.NUMBER_PO = data.at(PART_N).toUInt()+1;

            sre_list.push_back(QByteArray(static_cast<char*>(static_cast<void*>(&po)),sizeof(PO_CHECKSUM)));
            list.push_back("\t{" + QString::number(po.NUMBER_MODUL)     + ", " +
                                   QString::number(po.NUMBER_CPU)                               + ", " +
                                   QString::number(po.NUMBER_PO)                                  + ", " +
                                   "0x"+QString::number(po.CHECKSUM,16)              + "},\r\n");
        }
    }


    std::sort(sre_list.begin(),sre_list.end(),[](QByteArray& first, QByteArray& next)
    {
        if (first[0] == next[0])
            return first[8] < next[8];
        return first[0] < next[0];
    });

    PO_CHECKSUM last;
    sre_list.push_back(QByteArray(static_cast<char*>(static_cast<void*>(&last)),sizeof(PO_CHECKSUM)));
    list.push_back("};\r\n");
    if (manager)
    {
        manager->setFilePath(Storage::load()->options().loadpath + "/szi_" + Storage::load()->cfg().BlockName() + ".c");
        manager->write(list);
    }

    if (sre && sre->beginWrite(Storage::load()->options().loadpath +"/"+ file))
    {
        sre->write("rec_type:S0",sre_header);
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

