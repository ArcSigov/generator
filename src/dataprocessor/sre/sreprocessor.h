#include "dataprocessor.h"
#include <list>

class SreProcessor : public DataProcessor
{
    struct ID_PO_TYPE{
        unsigned char  identity[36] = {0};
        unsigned char  name[24] = {0};
        unsigned short ver{0};
        unsigned short red{0};
        unsigned char  date[12]={0};
        unsigned int   KS{0};
    };
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
