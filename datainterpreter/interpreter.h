#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <QObject>
#include <QVector>

class FileDataInterpreter : public QObject
{
    Q_OBJECT
    public:
    explicit FileDataInterpreter(QObject *parent = nullptr) : QObject(parent){};
    ~FileDataInterpreter() {};
public slots:
    virtual void readFileData(const QVector<QStringList>& l) = 0;
signals:
    void dataUpdated(bool);
};

#endif // INTERPRETER_H
