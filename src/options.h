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
    QString   loadpath{QDir::currentPath()};
    QString   kernelpath{QDir::currentPath()};
};


#endif
