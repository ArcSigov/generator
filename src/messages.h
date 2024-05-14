#pragma once

enum class MessageCategory
{
    def,
    run,
    info,
    notify,
    warning,
    error,
    update,
    stop,
    dataReady
};

struct ID_PO_TYPE{
    unsigned char  identity[36] = {0};
    unsigned char  name[24] = {0};
    unsigned short ver{0};
    unsigned short red{0};
    unsigned char  date[12]={0};
    unsigned int   KS{0};
};
