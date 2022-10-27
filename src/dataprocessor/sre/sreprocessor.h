#include "dataprocessor.h"

enum class RecType
{
    S1,
    S2,
    S3
};




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
public:
    SreProcessor(QObject* parent,const RecType& _record_type);
    ~SreProcessor(){}
    void process() override;
    void           write_sre(size_t base_addr, const QByteArrayList &data, QStringList &out);
    QByteArrayList read_sre(const QStringList &srec);
    void create_cfg();
private:
    size_t rec_size{0};
    RecType type{RecType::S3};
    QString header;
    QString terminate_str{"S70500000000FA"};
    QByteArrayList make_id(const DataStorage& data);
    void calc_checksumm(unsigned int &crc, QByteArrayList memory);
};
