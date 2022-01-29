#ifndef FILEREADER_H
#define FILEREADER_H

#include <QObject>
#include <QFile>
#include <QDebug>

class FileManager : public QObject
{
    Q_OBJECT
        public:
    explicit FileManager(QObject *parent = nullptr) : QObject(parent), f(new QFile(parent)){};
            ~FileManager(){};
public slots:
        virtual void readFile(const QString& path) = 0;
        virtual bool writeToFile(const QStringList& data) = 0;
        virtual void setFilePath(const QString& path) = 0;
signals:
        void readResult(const QVector<QStringList>& list);
        void saveResult(bool);
        void getDataToWrite(bool);
protected:
        QFile* f;
};


#endif
