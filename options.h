#ifndef OPTIONSHINCLUDED
#define OPTIONSHINCLUDED


#include <QString>
#include <QDir>

enum class BlockType
{
    undef,
    bis,
    bgs,
    bcvm
};

struct Settings
{
    BlockType type{BlockType::undef};
    QString   abspath{QDir::currentPath()};
};


#endif
