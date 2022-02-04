#include "cfginterpreter.h"

CfgDataProcessor::CfgDataProcessor(const BlockType &block)
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

void CfgDataProcessor::process()
{

}

void CfgDataProcessor::setBlockType(const BlockType& block)
{
    //*this = CfgDataInterpreter();
}

