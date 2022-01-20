#ifndef FILEREADER_H
#define FILEREADER_H

#include <QObject>
#include <QFile>
#include <QDebug>

class FileReader : public QObject
{
    Q_OBJECT
        public:
    explicit FileReader(QObject *parent = nullptr) : QObject(parent), f(new QFile(parent)){};
            ~FileReader(){};
public slots:
        virtual void readFile(const QString& path) = 0;        
signals:
        void Result(QVector<QStringList>& list);
protected:
        QFile* f;
};


#endif
