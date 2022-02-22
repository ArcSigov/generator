#include "batchprocessor.h"
#include <QDir>

BatchIdInfoProcessor::BatchIdInfoProcessor() :
    cur_id_path(QDir::currentPath() + "/ID_Info_con.exe " + QDir::currentPath() + "/conf.ini "),
    idInfoRes(" > " + QDir::currentPath() + "/log.ini")
{

}

/*!
Выполняет генерацию флагов работы программы Id_Info_Con.exe и передает его менеджеру командной строки на выполнение
*/
void BatchIdInfoProcessor::process()
{
    QString formatted = cur_id_path;
    for (auto it = storage->begin(); it != storage->end(); it++)
    {
        auto crc = it->at(CRC).toUInt();
        auto date = it->at(ID_DATE).toDate().toString(Qt::SystemLocaleShortDate).replace(".",":");

        formatted.push_back(it->genericType() ? " " : "-bs ");
        formatted.push_back(date.isEmpty() ? " " : " -d " + date);
        formatted.push_back(crc > 0  ? "-cs " + it->at(CRC).toString(): " ");
        formatted.push_back(idInfoRes);
    }
    if (manager) manager->write(QStringList(formatted));
}

void BatchCfgProcessor::process()
{
    QString str;
    for (const auto& it: qAsConst(CommandHeader))
        str.push_back(it);

    if (manager) manager->write(QStringList(str));
}

void BatchCfgProcessor::update()
{
    switch (settings->type)
    {
    case BlockType::bis:
    case BlockType::bcvm:
        CommandHeader[OUTPUT]      = settings->loadpath + (settings->type == BlockType::bis ? "/cfg_bis.mot" : "/cfg_bcvm.mot");
        CommandHeader[CFG_NAME]    = settings->loadpath + (settings->type == BlockType::bis ? "/cfg_bis.c" : "/cfg_bcvm.c");
        CommandHeader[COMLINE_ROM] = "bis_comline_rom.cmd";
        break;
    case BlockType::bgs:
        CommandHeader[OUTPUT]      = settings->loadpath + "/cfg_bgs.mot";
        CommandHeader[CFG_NAME]    = settings->loadpath + "/cfg_bgs.c";
        CommandHeader[COMLINE_ROM] = "bgs_comline_rom.cmd";
        break;
    case BlockType::undef:
    default:
        CommandHeader[CFG_NAME].clear();
        CommandHeader[OUTPUT].clear();
        CommandHeader[COMLINE_ROM].clear();
        return;
    }
    CommandHeader[OUTPUT].push_back('"');
    CommandHeader[OUTPUT].push_front('"');
}
