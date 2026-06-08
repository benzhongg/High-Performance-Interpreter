#include "instructionBuilder.h"

InstructionBuilder::InstructionBuilder()
{

}

Instruction::ADD* AddBuilder::create()
{
    Instruction::ADD res;
    return &res;
}