#include "datastorage.h"
#include "tablerowprop.h"

DataStorage::DataStorage()
{
   m_num = 0;
   f_path = "";
   date = QDate::currentDate();
   version = 0;
   crc = 0;
   description= " ";
   ram_addr = 0;
   n_part = 0;
}

DataStorage::DataStorage(const QVariant&v, int column) : DataStorage()
{
    SetValue(v,column);
}

DataStorage::~DataStorage()
{

}

QVariant DataStorage::GetValue(int column)
{
    switch (column)
    {
        case MODULE_NUM:
            return m_num;
        case FILE_PATH:
            return f_path;
        case ID_DATE:
            return date;
        case VERSION:
            return version;
        case CRC:
            return crc;
        case DESCRIPTION:
            return description;
        case RAM_ADDR:
            return ram_addr;
        case PART_N:
            return n_part;
        default : return 0;
    }
}

void DataStorage::SetValue(const QVariant& v, int column)
{
    switch (column)
    {
        case MODULE_NUM:
             m_num = v.toInt();
        case FILE_PATH:
             f_path = v.toString();
        case ID_DATE:
             date   = v.toDate();
        case VERSION:
             version = v.toInt();
        case CRC:
             crc = v.toInt();
        case DESCRIPTION:
             description = v.toString();
        case RAM_ADDR:
             ram_addr = v.toInt();
        case PART_N:
             n_part = v.toInt();
        default : break;
    }
}

