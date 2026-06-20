#include "instruction.h"

void Instruction::Base::read(FileReaderBase* fileReader)
{
    instructType = static_cast<InstructionType>(fileReader->get_uint32());
}


void Instruction::Add::read(FileReaderBase* fileReader)
{
    param1 = fileReader->get_uint32();
    param2 = fileReader->get_uint32();
}

void Instruction::Sub::read(FileReaderBase* fileReader)
{
    param1 = fileReader->get_uint32();
    param2 = fileReader->get_uint32();
}

void Instruction::Mul::read(FileReaderBase* fileReader)
{
    param1 = fileReader->get_uint32();
    param2 = fileReader->get_uint32();
}

void Instruction::Div::read(FileReaderBase* fileReader)
{
    param1 = fileReader->get_uint32();
    param2 = fileReader->get_uint32();
}

void Instruction::Store::read(FileReaderBase* fileReader)
{
    param1 = fileReader->get_uint32();
}

void Instruction::Compare::read(FileReaderBase* fileReader)
{
    param1 = fileReader->get_uint32();
    param2 = fileReader->get_uint32();
}

void Instruction::Print::read(FileReaderBase* fileReader)
{
    size = fileReader->get_uint32();
    printStr = fileReader->get_bytes(size);
}
