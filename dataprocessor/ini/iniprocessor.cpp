#include "iniprocessor.h"
#include "tablerowprop.h"


QString IniDataProcessor::quittance()
{
    if (m)
    {
        auto res = m->read("log.ini");
        if (res.size()>2) return res.at(2);
    }

    return {};
}

void IniDataProcessor::process()
{
    QString formatted;
    for (auto it = s->begin(); it != s->end() ; it++)
    {
        formatted.push_back("00000000\r\n");
        formatted.push_back(it->genericSize() + "\r\n");
        formatted.push_back(it->at(FILE_PATH).toString()+"\r\n");
        formatted.push_back(output_directory + "/"+it->genericName()+"\r\n"+" "+"\r\n");
        formatted.push_back(it->at(DESCRIPTION).toString()+"\r\n");
        formatted.push_back(it->at(VERSION).toString().rightJustified(2,'0') + " " + it->at(REVISION).toString().rightJustified(2,'0') + "\r\n");
    }

    if (m)
    {
        m->setFilePath("conf.ini");
        m->write(QStringList(formatted));
    }
}

void IniDataProcessor::setSettings(const Settings& _settings)
{
    output_directory = _settings.abspath;
}
