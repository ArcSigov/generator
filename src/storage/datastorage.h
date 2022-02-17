#pragma once

#include <QString>
#include <QVariant>
#include <QDate>
#include <QFileInfo>
#include "tablerowprop.h"

class DataStorage
{
    size_t  m_num{0};
    QString f_path{};
    QDate   date{QDate::currentDate()};
    size_t  version{0};
    size_t  revision{0};
    size_t  crc{0};
    QString description{};
    size_t  ram_addr{0};
    size_t  n_part{0};
    size_t  generic_size{0};
    QString generic_name{};
    size_t  rom_addr{0};
public:
    DataStorage() = default;
    ~DataStorage() = default;
    QVariant at(const int &column);
    QVariant at(const int &column) const;
    void     set(const QVariant &v, int column);
    bool     isValid(const int& column);
    static QString  name(const int &column);
    QString genericName();
    size_t  fileSize();
    size_t  fileSize() const;
    QString genericIniSize();
    size_t  genericType();
    QString genericName() const;
    QString genericIniSize() const;
    size_t  genericType() const;
    size_t  romAddr();
    size_t  romAddr() const;
    void    setRomAddr(const size_t& _addr);
private:
    QFileInfo info;
};
