#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <QString>
#include <QVariant>
#include <QDate>

class DataStorage
{
    size_t  m_num;
    QString f_path;
    QDate   date;
    size_t  version;
    size_t  revision;
    size_t  crc;
    QString description;
    size_t  ram_addr;
    size_t  n_part;
public:
    DataStorage();
    ~DataStorage();
    QVariant at(const int &column);
    void     set(const QVariant &v, int column);
    bool     isValid(const int& column);
    static QString  name(const int &column);
};

#endif // DATASTORAGE_H
