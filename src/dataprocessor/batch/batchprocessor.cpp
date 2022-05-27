#include "batchprocessor.h"
#include <QDir>


/*!
Выполняет генерацию флагов работы программы Id_Info_Con.exe и передает его менеджеру командной строки на выполнение
*/
void BatchIdInfoProcessor::process()
{
    for (const auto& it : Storage::load()->data())
    {
        if (!it.at(IS_CHECKED).toBool())
            continue;

        QString formatted = cur_id_path + it.genericName().replace('.','_') + ".ini ";

        auto crc = it.at(CRC).toUInt();
        auto date = it.at(ID_DATE).toDate().toString(Qt::SystemLocaleShortDate).replace(".",":");

        formatted.push_back(it.genericType() ? " " : "-bs ");
        formatted.push_back(date.isEmpty() ? " " : " -d " + date);
        formatted.push_back(crc > 0  ? " -cs " + QString::number(it.at(CRC).toUInt(),16): " ");
        formatted.push_back(" > " + QDir::currentPath() + "/" + it.genericName().replace('.','_') + "_log.ini");
        emit sendMessage(MessageCategory::info,"Генерирую " + it.genericName());
        if (manager) manager->write(QStringList(formatted));
    }
}

void BatchCfgProcessor::process()
{
    QString str;
    auto name = Storage::load()->options().loadpath + "/cfg_" + Storage::load()->cfg().BlockName();
    commandHeader[CFG_NAME] = name + ".c";
    commandHeader[OUTPUT]   = '"' + name + ".mot" + '"';
    commandHeader[COMLINE_ROM] = QDir::currentPath() + "/" + Storage::load()->cfg().ComlineRom();

    for (const auto& it: qAsConst(commandHeader))
        str.push_back(it);

    if (manager) manager->write(QStringList(str));
}

