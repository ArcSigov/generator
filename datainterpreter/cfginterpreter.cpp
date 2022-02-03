#include "cfginterpreter.h"

CfgDataInterpreter::CfgDataInterpreter(const BlockType &block)
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

void CfgDataInterpreter::write([[maybe_unused]] const DataStorage &storage)
{

}

void CfgDataInterpreter::setBlockType(const BlockType& block)
{
    //*this = CfgDataInterpreter();
}

