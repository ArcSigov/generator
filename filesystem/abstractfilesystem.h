#ifndef ABSTRACTFILESYSTEM_H
#define ABSTRACTFILESYSTEM_H

#include <QObject>
#include <QFile>
#include <QDebug>

class AbstractFileSystem : public QObject
{
    Q_OBJECT
        public:
    explicit AbstractFileSystem(QObject *parent = nullptr) : QObject(parent){};
            ~AbstractFileSystem(){};
public slots:
        virtual void readFile(const QString& path) = 0;        
signals:
        void Result(QVector<QStringList>& list);
};


class FileSystem : public AbstractFileSystem
{
    Q_OBJECT
public:
    explicit FileSystem(QObject *parent = nullptr);
    ~FileSystem();
public slots:
    virtual void readFile(const QString& path) override;

};

#endif // ABSTRACTFILESYSTEM_H
