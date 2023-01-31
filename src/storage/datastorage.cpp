#include "datastorage.h"
#include "tablerowprop.h"


QVariant DataStorage::at(const int& column)
{   
    switch (column)
    {
        case IS_CHECKED:  return isChecked;
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
        case IS_CHECKED:  return isChecked;
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
        case IS_CHECKED:    return false;
        case MODULE_NUM:
        {
            for (const auto &m: m_num.split(','))
            {
                auto val = m.toUInt(nullptr,16);
                if (val < 0x25 || val > 0x49)
                    return true;
            }
            return false;
        };
        case FILE_PATH:     return f_path.isEmpty();
        case ID_DATE:       return date.isNull();
        case VERSION:       return false;
        case REVISION:      return false;
        case CRC:           return crc == 0;
        case DESCRIPTION:   return description.isEmpty();
        case RAM_ADDR:      return ram_addr == 0;
        case PART_N:        return n_part > 3;
        default :           return 0;
    }
}

bool DataStorage::isValid(const int &column) const
{
    switch (column)
    {
    case IS_CHECKED:    return false;
    case MODULE_NUM:
    {
        for (const auto &m: m_num.split(','))
        {
            auto val = m.toUInt(nullptr,16);
            if (val < 0x25 || val > 0x49)
                return true;
        }
        return false;
    }
    case FILE_PATH:     return f_path.isEmpty();
    case ID_DATE:       return date.isNull();
    case VERSION:       return false;
    case REVISION:      return false;
    case CRC:           return crc != 0;
    case DESCRIPTION:   return description.isEmpty();
    case RAM_ADDR:      return ram_addr == 0;
    case PART_N:        return n_part > 3;
    default :           return 0;
    }
}


void DataStorage::set(const QVariant& v, int column)
{
    switch (column)
    {
        case IS_CHECKED:  isChecked = v.toBool();      break;
        case MODULE_NUM:  m_num = v.toString();        break;
        case ID_DATE:     date   = v.toDate();         break;
        case VERSION:     version = v.toUInt();        break;
        case REVISION:    revision = v.toUInt();       break;
        case CRC:         crc = v.toUInt();            break;
        case DESCRIPTION: description = v.toString();  break;
        case RAM_ADDR:    ram_addr = v.toUInt();       break;
        case PART_N:      n_part = v.toUInt();         break;
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
        case IS_CHECKED:    return "Активно";
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

QString DataStorage::genericName()
{
    return generic_name;
}

size_t  DataStorage::genericType()
{
    return info.completeSuffix() == "elf" ? 0 : 1;
}

QString DataStorage::genericIniSize()
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

QString DataStorage::genericIniSize() const
{
    return QString::number(generic_size-4,16).rightJustified(8,'0');
}

void DataStorage::setRomAddr(const size_t &_addr)
{
    rom_addr = _addr;
}

size_t DataStorage::romAddr()
{
    return rom_addr;
}

size_t DataStorage::romAddr() const
{
    return rom_addr;
}

size_t DataStorage::fileSize()
{
    return generic_size;
}

size_t DataStorage::fileSize() const
{
    return generic_size;
}
