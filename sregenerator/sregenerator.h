#ifndef SREGEN_H_INCLUDED
#define SREGEN_H_INCLUDED

#include <QString>
#include <QTextStream>
#include <QFileInfo>
#include <QDir>
#include <vector>

struct ID_PO_TYPE
{
    unsigned int   reserved;
    unsigned char  identity[36];
    unsigned char  name[24];
    unsigned short ver;
    unsigned short red;
    unsigned char  date[12];
    unsigned int   KS;
    void clear()
    {
        ver = 0;
        red = 0;
        KS = 0;
        reserved = 0;
        memset(identity,' ',36);
        memset(name,' ',24);
        memset(date,' ',12);
    }
    ID_PO_TYPE()
    {
        clear();
    }
};

class SreGen
{
    QFile input,output;
    QTextCodec* codec;
    ID_PO_TYPE id;
    QByteArray ba;
public:
    SreGen();
    ~SreGen();
    void GenerateNewSre(const QString &input_file_name, const QString &output_file_name);
    void SetIdPO(const QString& date, const QString& version,const QString& edition, const QString& crc, const QString& description);
    const auto& GetCrc() const;
private:
    QString _make_byte(QString str, int size);
    void _read_bytes(QVector<unsigned char>& v, const  QByteArray& bytes);
    void _write_bytes(const unsigned int& addr,unsigned char* bytes, const size_t& bytes_count, QTextStream& stream,const bool& end = false);
    void calc_checksumm(unsigned int& crc,unsigned int* in,size_t count);
};



#endif
