#include "txtdataprocessor.h"






void IdentityDataProcessor::process()
{
    QStringList out;
    QString separateline = "---------------------------------------------------------------------------------\r\n";
    out.push_back(separateline);
    out.push_back("|             Идентификатор    		  | Версия |    Дата    | Контрольная сумма |\r\n");
    out.push_back(separateline);

    for (const auto& data : Storage::load()->data())
    {
        QString line = "|"+data.at(DESCRIPTION).toString().leftJustified(36,' ') +            " |  " +
                       data.at(VERSION).toString() + "." + data.at(REVISION).toString() + "   | " +
                       data.at(ID_DATE).toDate().toString(Qt::SystemLocaleShortDate) +    " | " +
                       QString::number(data.at(CRC).toUInt(),16).rightJustified(12,' ') + "      |\r\n";
        out.push_back(line);
        out.push_back(separateline);
    }

    if (manager)
    {
        manager->setFilePath(Storage::load()->options().loadpath + "/идентификационная информация.txt");
        manager->write(out);
    }
}
