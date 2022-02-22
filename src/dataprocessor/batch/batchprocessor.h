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
    explicit BatchIdInfoProcessor();
    ~BatchIdInfoProcessor() = default;
    virtual void process() override;
    virtual void update() override{}
private:
    QString cur_id_path;    ///< путь, по которому Id_Info_Con.exe выполнит запуск скрипта .ini файла
    QString idInfoRes;    ///< путь, по которому необходимо сохранить результат выполнения скрипта
};

class BatchCfgProcessor : public DataProcessor
{
    enum
    {
        CFG_NAME = 1,
        COMLINE_ROM = 3,
        OUTPUT = 5
    };
public:
    explicit BatchCfgProcessor() = default;
    ~BatchCfgProcessor() = default;
    virtual void process() override;
    virtual void update() override;
private:
    QStringList CommandHeader{{QDir::currentPath()+"/Tools4x/bin/mipsel-elf32-gcc.exe -g -c -O0 -EL -o cfg_files.o "},
                              {},   //what a cfg block name
                              {" && " + QDir::currentPath()+"/Tools4x/bin/mipsel-elf32-ld.exe -d -g -EL -T "},
                              {},   //what a comline rom
                              {" && copy cfg_files.mot "},
                              {} //where
                              };
};
