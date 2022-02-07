#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <QString>
#include <QVariant>
#include <QDate>
#include <QFileInfo>

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
    size_t  generic_size;
    QString generic_name;
public:
    DataStorage();
    ~DataStorage();
    QVariant at(const int &column);
    QVariant at(const int &column) const;
    void     set(const QVariant &v, int column);
    bool     isValid(const int& column);
    static QString  name(const int &column);
    QString genericName();
    QString genericSize();
    size_t  genericType();
    QString genericName() const;
    QString genericSize() const;
    size_t  genericType() const;
private:
    QFileInfo info;
};

#endif // DATASTORAGE_H
