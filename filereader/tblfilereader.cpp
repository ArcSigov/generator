#include "tblfilereader.h"


TblFileReader::TblFileReader(QObject* parent) :
    FileReader(parent)
{

}


TblFileReader::~TblFileReader()
{

}

void TblFileReader::readFile(const QString &path)
{
    QFile* f = new QFile(path,this);
    if (f->open(QIODevice::ReadOnly))
    {
        QVector<QStringList> l;
        QTextStream s(f);
        while (!s.atEnd())
        {
            auto string = s.readLine();
            l.push_back(string.split(";"));
        }
        emit Result(l);
        f->close();
    }
}
