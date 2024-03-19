#include "generator.h"
#include "tblprocessor.h"
#include "txtdataprocessor.h"
#include "filemanager.h"
#include "sremanager.h"
#include "sreprocessor.h"
#include "cfgprocessor.h"
#include "verifydataprocessor.h"
#include "sziprocessor.h"

Generator::Generator(QObject *parent) : QObject(parent)
{
    managers.push_back(new FileManager());
    managers.push_back(new SreManager());    
    processors[new TblDataProcessor(this)] = nullptr;
    processors[new CfgDataProcessor(managers.back(),this)] = nullptr;
    processors[new FlashSwTxtDataProcessor(this)] = &Storage::load()->options().romSW_enabled;
    processors[new FlashRsTxtDataProcessor(this)] = &Storage::load()->options().romRS232_enabled;
    processors[new RamSwTxtDataProcessor(this)]   = &Storage::load()->options().ramSW_enabled;
    processors[new VerifyDataProcessor(this)]   = nullptr;
    processors[new SreProcessor(this,managers.back())]   = nullptr;
    processors[new SziDataProcessor(managers.back(),this)]= nullptr;
    processors[new IdentityDataProcessor(this)]   = nullptr;

    for (const auto& it : processors)
    {
        it.first->setFileManager(managers[0]);
        QObject::connect(it.first, &DataProcessor::sendMessage, this, &Generator::sendMessage);
    }
}


/*!
Выполняет запуск процессов генерации исходного кода, загрузочных файлов, файлов конфигурации
\param[in] flag Разрешение работать
*/
void Generator::run()
{
    emit sendMessage(MessageCategory::run);
    for (const auto& it :  processors)
    {
        if(!dynamic_cast<TblDataProcessor*>(it.first) && !dynamic_cast<VerifyDataProcessor*>(it.first))
        {
            if (it.first && (!it.second || *it.second))
                it.first->process();
        }
    }
    emit sendMessage(MessageCategory::stop);
}

/*!
Выполняет чтение файла с настройками и данными для работы
\param[in] &path ссылка на местоположение файла
*/
void Generator::readTblFile(const QString &path)
{
    if (path.isEmpty()) return;
    for (const auto& it : processors)
    {
        auto tbl = dynamic_cast<TblDataProcessor*>(it.first);
        if (tbl)
        {
            tbl->setMode(path,TblMode::read);
            tbl->process();
            break;
        }
    }
}

/*!
Выполняет сохранение файла с настройками и данными
\param[in] &path ссылка на место сохранения файла
*/
void Generator::saveTblFile(const QString &path)
{
    if (path.isEmpty()) return;
    for (const auto& it : processors)
    {
        auto tbl = dynamic_cast<TblDataProcessor*>(it.first);
        if (tbl)
        {
            tbl->setMode(path,TblMode::write);
            tbl->process();
            break;
        }
    }
}

/*!
Выполняет верификацию файла с контрольными суммами с табличными
\param[in] &path ссылка на место сохранения файла
*/
void Generator::runVerify(const QString& verifyFile)
{
    if (verifyFile.isEmpty()) return;
    for (const auto& it: processors)
    {
        auto vrf = dynamic_cast<VerifyDataProcessor*>(it.first);
        if (vrf)
        {
            vrf->setPath(verifyFile);
            emit sendMessage(MessageCategory::run);
            vrf->process();
            emit sendMessage(MessageCategory::stop);
        }
    }
}
