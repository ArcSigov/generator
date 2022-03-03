/*!
\file batchprocessor.h
\brief Заголовочный файл с описанием методов класса BatchProcessor (формирует информацию для выполнения ее в командной строке)
\authors Аркадий Сигов
Данный файл содержит в себе определения методов класса, используемых в программе
*/

#pragma once


#include "dataprocessor.h"

class BatchIdInfoProcessor : public DataProcessor
{
public:
    explicit BatchIdInfoProcessor() = default;
    ~BatchIdInfoProcessor() = default;
    void process() override;
private:
    QString cur_id_path{QDir::currentPath() + "/ID_Info_con.exe " + QDir::currentPath() + "/"};    ///< путь, по которому Id_Info_Con.exe выполнит запуск скрипта .ini файла
};

class BatchCfgProcessor : public DataProcessor
{
public:
    explicit BatchCfgProcessor() = default;
    ~BatchCfgProcessor() = default;
    void process() override;
};
