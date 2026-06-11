#include "instruction.h"

void Instruction::Base::read(FileReaderBase* fileReader)
{
    instructType = static_cast<InstructionType>(fileReader->get_uint8());
}


void Instruction::Add::read(FileReaderBase* fileReader)
{
    param1 = fileReader->get_uint8();
    param2 = fileReader->get_uint8();
}
