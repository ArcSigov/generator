#ifndef FILEREADER_H
#define FILEREADER_H

#include <QObject>
#include <QFile>
#include <QDebug>

class AbstractFileManager : public QObject
{
    Q_OBJECT
        public:
    explicit AbstractFileManager(QObject *parent = nullptr) : QObject(parent), f(new QFile(parent)){};
            ~AbstractFileManager(){};
public slots:
        virtual QStringList readFile(const QString& path) = 0;
        virtual bool writeToFile(const QStringList& data) = 0;
        virtual void setFilePath(const QString& path) = 0;
protected:
        QFile* f;
};


#endif
