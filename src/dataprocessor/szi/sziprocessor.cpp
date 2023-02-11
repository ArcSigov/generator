#include "sziprocessor.h"
#include "sziprocessorlocal.h"
#include <QStringList>
#include <QDebug>


SziDataProcessor::SziDataProcessor(DataProcessor* _sre,QObject *parent)
    : DataProcessor{parent},sre{_sre}
{

}

void SziDataProcessor::process()
{
    QStringList list;
    QByteArray  data;

    for (const auto& data: Storage::load()->data())
    {
        for (const auto& la: data.at(MODULE_NUM).toString().split(","))
        {
//            PO_CHECKSUM po;
//            po.NUMBER_MODUL =
            //qDebug() << "{ " + Storage::load()->cfg().getLaName(la.toUInt(nullptr,16)) + ", " + getStrCpu(la.toUInt(nullptr,16)) + ", " + getStrPos(data.at(PART_N).toUInt());
        }
    }
}


QString SziDataProcessor::getStrCpu(size_t la)
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
            return "CPU1";
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
            return "CPU2";
        default:break;
    }
    return {};
}

QString SziDataProcessor::getStrPos(size_t pos)
{
    switch (pos+1)
    {
        case 1:
            return "NUM_CONFIG";
        case 2:
            return "NUM_PARTITION_1";
        case 3:
            return "NUM_PARTITION_2";
        case 4:
            return "NUM_PARTITION_3";
    }

    return {};
}
