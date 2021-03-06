#include "datastorage.h"
#include "tablerowprop.h"
#include <QDebug>
DataStorage::DataStorage()
{
   m_num = 0;
   f_path.clear();
   date = QDate::currentDate();
   version = 0;
   revision = 0;
   crc = 0;
   description.clear();
   ram_addr = 0;
   n_part = 0;
   generic_name.clear();
   generic_size = 0;
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


QVariant DataStorage::at(const int& column) const
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
        case ID_DATE:     date   = v.toDate();        break;
        case VERSION:     version = v.toInt();        break;
        case REVISION:    revision = v.toInt();       break;
        case CRC:         crc = v.toInt();            break;
        case DESCRIPTION: description = v.toString(); break;
        case RAM_ADDR:    ram_addr = v.toInt();       break;
        case PART_N:      n_part = v.toInt();         break;
        case FILE_PATH:
        {
            generic_name.clear();
            f_path = v.toString();
            info.setFile(f_path);
            generic_size = info.size()+84;
            while (generic_size % 4096 != 0 ) generic_size++;
            generic_name.push_back(info.baseName());
            generic_name.push_back(info.completeSuffix() == "elf" ? "_sum.sre" : "_sum.mot");
            break;
        }
        default : break;
    }
}

QString DataStorage::name(const int& column)
{
    switch(column)
    {
        case MODULE_NUM:    return "??????????";
        case FILE_PATH:     return "????????";
        case ID_DATE:       return "????????";
        case VERSION:       return "????????????";
        case REVISION:      return "????????????????";
        case CRC:           return "????";
        case DESCRIPTION:   return "????????????????";
        case RAM_ADDR:      return "?????????? ??????";
        case PART_N:        return "????????????";
        default:break;
    }
    return QString();
}

QString DataStorage::genericName()
{
    return generic_name;
}

size_t  DataStorage::genericType()
{
    return info.completeSuffix() == "elf" ? 0 : 1;
}

QString DataStorage::genericSize()
{
    return QString::number(generic_size-4,16).rightJustified(8,'0');
}

QString DataStorage::genericName() const
{
    return generic_name;
}

size_t  DataStorage::genericType() const
{
    return info.completeSuffix() == "elf" ? 0 : 1;
}

QString DataStorage::genericSize() const
{
    return QString::number(generic_size-4,16).rightJustified(8,'0');
}
