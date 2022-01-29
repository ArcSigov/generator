#include "datastorage.h"
#include "tablerowprop.h"

DataStorage::DataStorage()
{
   m_num = 0;
   f_path = "";
   date = QDate::currentDate();
   version = 0;
   revision = 0;
   crc = 0;
   description= " ";
   ram_addr = 0;
   n_part = 0;
}

DataStorage::~DataStorage()
{

}

QVariant DataStorage::at(const int& column)
{
    switch (column)
    {
        case MODULE_NUM:  return m_num;
        case FILE_PATH:   return f_path;
        case ID_DATE:     return date;
        case VERSION:     return version;
        case REVISION:    return revision;
        case CRC:         return crc;
        case DESCRIPTION: return description;
        case RAM_ADDR:    return ram_addr;
        case PART_N:      return n_part;
        default :         return 0;
    }
}

bool DataStorage::isValid(const int &column)
{
    switch (column)
    {
        case MODULE_NUM:    return m_num < 25 || m_num > 49;
        case FILE_PATH:     return f_path.isEmpty();
        case ID_DATE:       return date.isNull();
        case VERSION:       return false;
        case REVISION:      return false;
        case CRC:           return crc == 0;
        case DESCRIPTION:   return description.isEmpty();
        case RAM_ADDR:      return ram_addr == 0;
        case PART_N:        return n_part < 1 || n_part > 3;
        default :           return 0;
    }
}

void DataStorage::set(const QVariant& v, int column)
{
    switch (column)
    {
        case MODULE_NUM:  m_num = v.toInt();          break;
        case FILE_PATH:   f_path = v.toString();      break;
        case ID_DATE:     date   = v.toDate();        break;
        case VERSION:     version = v.toInt();        break;
        case REVISION:    revision = v.toInt();       break;
        case CRC:         crc = v.toInt();            break;
        case DESCRIPTION: description = v.toString(); break;
        case RAM_ADDR:    ram_addr = v.toInt();       break;
        case PART_N:      n_part = v.toInt();         break;
        default : break;
    }
}

QString DataStorage::name(const int& column)
{
    switch(column)
    {
        case MODULE_NUM:    return "Адрес";
        case FILE_PATH:     return "Файл";
        case ID_DATE:       return "Дата";
        case VERSION:       return "Версия";
        case REVISION:      return "Редакция";
        case CRC:           return "КС";
        case DESCRIPTION:   return "Описание";
        case RAM_ADDR:      return "Адрес ОЗУ";
        case PART_N:        return "Раздел";
        default:break;
    }
    return QString();
}
