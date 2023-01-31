#include "verifydataprocessor.h"
#include <QDebug>

VerifyDataProcessor::VerifyDataProcessor(QObject *parent)
    : DataProcessor{parent}
{

}

void VerifyDataProcessor::setPath(const QString& _path)
{
    path = _path;
}

void VerifyDataProcessor::process()
{
    auto data = manager->read(nullptr,path);
    bool start = false;
    for (const auto& line:data)
    {
        if (!start)
        {
            start = line.contains("CHECKSUMMS_START");
            if (start) continue;
        }
        else
        {
            if (line.contains("CHECKSUMMS_END"))
                break;

            compare_string(line);
        }
    }
}

void VerifyDataProcessor::compare_string(const QString& current)
{
    auto params = current.split(";");
    if (!params.empty())
    {
        for (const auto& data : Storage::load()->data())
        {
            if (data.at(DESCRIPTION) == params.front() && params.size() == 4)
            {
                bool error = false;
                emit sendMessage(MessageCategory::update,"Проверка " + data.at(DESCRIPTION).toString());
                auto verrev = params.at(1).split(".");
                if (data.at(VERSION) != verrev.at(0))
                {
                    emit sendMessage(MessageCategory::error,"Ошибка версии, ожидается:" + data.at(VERSION).toString() + " обнаружена: " + verrev.at(0));
                }
                if (data.at(REVISION) != verrev.at(1))
                {
                    emit sendMessage(MessageCategory::error,"Ошибка подверсии, ожидается:" + data.at(REVISION).toString() + " обнаружена: " + verrev.at(1));
                }
                if (data.at(ID_DATE).toDate().toString(Qt::SystemLocaleShortDate) != params.at(2))
                {
                    emit sendMessage(MessageCategory::error,"Ошибка даты, ожидается:" + data.at(ID_DATE).toDate().toString(Qt::SystemLocaleShortDate) + " обнаружена: " + params.at(2));
                }
                if (data.at(CRC) != params.at(3).toUInt(nullptr,16))
                {
                    emit sendMessage(MessageCategory::error,"Ошибка контрольной суммы, ожидается:" + QString::number(data.at(CRC).toUInt(),16) + " обнаружена: " + params.at(3));
                }
//                else
//                {
//                    qDebug() << "ok";
//                }
            }
        }
//        qDebug() << params;
    }
}
