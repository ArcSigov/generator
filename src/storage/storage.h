#pragma once

#include "datastorage.h"
#include "configuration.h"
#include "tablerowprop.h"
#include "messages.h"

class Storage : public QObject
{
    Q_OBJECT
public:
    static Storage*           load();
    std::vector<DataStorage>& data();
    Options&                  options();
    Configuration&            cfg();
signals:
    void sendMessage(const MessageCategory&,const QString& = {});
public slots:
    void sort();
    void calcRom();
private:
    Storage(){}
    Storage(const Storage&) = delete;
    Storage& operator=(const Storage&) = delete;
    std::vector<DataStorage> store;
    Options _settings;
    Configuration conf{"settings.json"};
};

