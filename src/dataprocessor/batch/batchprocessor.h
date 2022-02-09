/*!
\file batchprocessor.h
\brief Заголовочный файл с описанием методов класса BatchProcessor (формирует информацию для выполнения ее в командной строке)
\authors Аркадий Сигов
Данный файл содержит в себе определения методов класса, используемых в программе
*/

#pragma once


#include "dataprocessor.h"

class BatchProcessor : public DataProcessor
{
public:
    explicit BatchProcessor();
    ~BatchProcessor() = default;
    virtual void process() override;
private:
    QString cur_id_path;    ///< путь, по которому Id_Info_Con.exe выполнит запуск скрипта .ini файла
    QString result_path;    ///< путь, по которому необходимо сохранить результат выполнения скрипта
};
