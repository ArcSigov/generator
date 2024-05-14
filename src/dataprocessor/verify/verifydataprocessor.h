/*!
\file verifydataprocessor.h
\brief Заголовочный файл с описанием методов класса VerifyDataProcessor (выполняет сличение пользовательских данных о идентификаторах с результатами выполнения программы)
\authors Аркадий Сигов
Данный файл содержит в себе определения методов класса, используемых в программе
*/


#ifndef VERIFYDATAPROCESSOR_H
#define VERIFYDATAPROCESSOR_H

#include "dataprocessor.h"

class VerifyDataProcessor : public DataProcessor
{
    Q_OBJECT
public:
    explicit VerifyDataProcessor(QObject *parent = nullptr);
    void setPath(const QString& path);
    void process();
signals:

private:
    QString path{};
    void compare_string(const QString& current);
};

#endif // VERIFYDATAPROCESSOR_H
