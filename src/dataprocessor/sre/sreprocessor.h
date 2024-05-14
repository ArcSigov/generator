/*!
\file sreprocessor.h
\brief Заголовочный файл с описанием методов класса SreProcessor (выполняет генерацию файлов в формате записи данных Motorola, S-Record)
\authors Аркадий Сигов
Данный файл содержит в себе определения методов класса, используемых в программе
*/

#include "dataprocessor.h"
#include <list>

class SreProcessor : public DataProcessor
{

    struct bitfield_t
    {
        unsigned int hi{0};
        unsigned int lo{0};
    };
public:
    SreProcessor(QObject* parent, Manager *sre);
    ~SreProcessor();
    void process() override;
private:
    QByteArrayList make_id(const DataStorage& data);
    void calc_checksumm(unsigned int &crc, QByteArrayList memory);
    void remake_id(QByteArrayList& id, const size_t& res, const size_t& crc);
    Manager* sre_manager;
};
