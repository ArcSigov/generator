#include "cfginterpreter.h"

CfgDataInterpreter::CfgDataInterpreter(BlockType block)
{
    switch (block)
    {
    case BlockType::bis:
        break;
    case BlockType::bgs:
        break;
    case BlockType::bcvm:
        break;
    case BlockType::undef:
        break;
    }
}

CfgDataInterpreter::~CfgDataInterpreter()
{

}

void CfgDataInterpreter::write([[maybe_unused]] DataStorage* storage)
{

}

void CfgDataInterpreter::setBlockType(const BlockType& block)
{
    *this = CfgDataInterpreter(block);
}

