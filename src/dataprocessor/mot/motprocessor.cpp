#include "motprocessor.h"
#include <QDebug>
#include <unordered_map>


MotDataProcessor::MotDataProcessor(QObject *parent) : DataProcessor{parent}
{

}

void MotDataProcessor::process()
{
    for (const auto &data: Storage::load()->data())
    {
        if (data.genericType())
        {
            tag_t* tags[TAG_COUNT];
            auto buf                      = manager->read(data.at(FILE_PATH).toString());
            auto tag_header               = reinterpret_cast<tag_storage_header_t*>(buf.data());
            auto tag_area                 = reinterpret_cast<unsigned char*>(buf.data() + tag_header->header_size);
            auto data_area                = tag_area  + (tag_header->tag_size * tag_header->tag_count);
            mot.string_area               = data_area + tag_header->data_size;
            tags[PARTITIONS_CFG_INFO_TAG] = find_tag(PARTITIONS_CFG_INFO_TAG_NAME,    tag_area , tag_header -> tag_count);
            tags[STASKS_CFG_INFO_TAG]     = find_tag(STASKS_CFG_INFO_TAG_NAME,           tag_area , tag_header -> tag_count);
            const auto& module            = data.at(MODULE_NUM).toString().toStdString();

            if (tags[PARTITIONS_CFG_INFO_TAG])
            {
               mot.part_count = tags[PARTITIONS_CFG_INFO_TAG]->data.v.value_size / sizeof(ke_conf_partition_t);
               mot.part_area  = (ke_conf_partition_t*)(data_area+tags[PARTITIONS_CFG_INFO_TAG]->data.v.value_offset);

               for (auto i = 0 ; i < mot.part_count; i++)
               {
                    addrs[module].push_back((char*)(mot.string_area + mot.part_area->app_file_name_off));
                    mot.part_area++;
               }
            }
            if (tags[STASKS_CFG_INFO_TAG])
            {
                mot.swm_area = (ke_conf_system_task_t*)(data_area+tags[STASKS_CFG_INFO_TAG]->data.v.value_offset);
                addrs[module].push_front((char*)(mot.string_area + mot.swm_area->cfg_string_off));
            }
        }
    }

    for (auto &data: Storage::load()->data())
    {
       data.set(find_addr(data.at(MODULE_NUM).toString().split(",").front(),data.baseName(),data.genericType()).toUInt(nullptr,16),RAM_ADDR);
       emit sendMessage(MessageCategory::update);
    }
}

tag_t* MotDataProcessor::find_tag(const char* tag_name, unsigned char* tag_area, size_t tag_count)
{
    auto tag = (tag_t*)tag_area;
    for (auto i = 0 ; i < tag_count; i++)
    {
        if (!strncmp((char*)(mot.string_area+tag->name_offset),tag_name,strlen(tag_name)))
            return tag;
        tag++;
    }
    return NULL;
}

QString MotDataProcessor::find_addr(const QString& module_num,const QString& part_name,const size_t& type)
{
    auto val = addrs.find(module_num.toStdString());
    if (val != addrs.end() && val->second.size())
    {
        if (type)
        {
            return "0x"+val->second.front().split("_").front();
        }
        else
        {
            for (const auto& addr: qAsConst(val->second))
                if (addr.contains(part_name))
                    return "0x"+addr.split("_").front();
        }
    }
    return {};
}
