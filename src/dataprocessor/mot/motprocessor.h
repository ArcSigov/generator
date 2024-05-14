#ifndef MOTPROCESSOR_H
#define MOTPROCESSOR_H

#include <dataprocessor.h>
#include <QObject>
#include "swm_cfg.h"
#include "tag_storage.h"
#include "ke_errors.h"
#include "ke_conf_module.h"

class MotDataProcessor : public DataProcessor
{
    struct mot_t
    {
        unsigned char* buf;
        unsigned char* string_area;
        size_t size;
        ke_conf_partition_t* part_area;
        ke_conf_rset_t*      rset_area;
        ke_conf_sport_t*     sport_area;
        ke_conf_qport_t*     qport_area;
        ke_conf_system_task_t* swm_area;
        size_t               swm_count;
        size_t               part_count;
        size_t               rset_count;
    };

    enum
    {
        PART,
        SWM,
        MEMREGIONS_CFG_INFO_TAG = 0,
        MEMMAPPINGS_CFG_INFO_TAG,
        SPORTS_CFG_INFO_TAG,
        QPORTS_CFG_INFO_TAG,
        RESOURCE_SETS_CFG_INFO_TAG,
        SNODES_CFG_INFO_TAG,
        QNODES_CFG_INFO_TAG,
        PARTITIONS_CFG_INFO_TAG,
        PART_HM_TBLS_CFG_INFO_TAG,
        PWINDOWS_CFG_INFO_TAG,
        STASKS_CFG_INFO_TAG,
        MODULE_CFG_INFO_TAG,
        SWM_CFG_INFO_TAG,
        TAG_COUNT
    };
public:
    explicit MotDataProcessor(QObject *parent = nullptr);
    void process() override;
private:
    mot_t mot;
    tag_t* find_tag(const char* tag_name, unsigned char* tag_area, size_t tag_count);
    QString find_addr(const QString& module_num,const QString& part_name,const size_t& type);
    std::unordered_map<std::string,QStringList> addrs;
};

#endif // MOTPROCESSOR_H
