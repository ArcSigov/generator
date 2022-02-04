#include "iniprocessor.h"
#include "tablerowprop.h"


QString IniDataProcessor::quittance()
{
    auto res = m->read("log.ini");

    if (res.size()>2)
        return res.at(2);

    //emit status(log.at(2));
}

void IniDataProcessor::process()
{

    m->setFilePath("conf.ini");
    QString formatted;
    for (auto it = s->begin(); it != s->end() ; it++)
    {
        formatted.push_back("00000000\r\n");
        formatted.push_back(it->genericSize() + "\r\n");
        formatted.push_back(it->at(FILE_PATH).toString()+"\r\n");
        formatted.push_back(it->genericName()+"\r\n"+" "+"\r\n");
        formatted.push_back(it->at(DESCRIPTION).toString()+"\r\n");
        formatted.push_back(it->at(VERSION).toString().rightJustified(2,'0') + " " + it->at(REVISION).toString().rightJustified(2,'0') + "\r\n");
    }
    m->write(QStringList(formatted));
}
