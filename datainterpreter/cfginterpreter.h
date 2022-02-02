#ifndef CFGINTERPRETER_H
#define CFGINTERPRETER_H

#include "interpreter.h"
#include <QVector>



enum class BlockType
{
    undef,
    bis,
    bgs,
    bcvm
};

class CfgDataInterpreter : public FileDataInterpreter
{
public:
    explicit CfgDataInterpreter(BlockType block = BlockType::undef);
    ~CfgDataInterpreter();
    virtual void write(DataStorage* storage = nullptr) override;
    void setBlockType(const BlockType& = BlockType::undef);
};

#endif
