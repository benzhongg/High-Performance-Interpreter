#include "instruction.h"

void Instruction::Base::read(std::shared_ptr<FileReaderBase> fileReader)
{
      instructType = static_cast<InstructionType>(fileReader->get_uint32());
}

void Instruction::Add::read(std::shared_ptr<FileReaderBase> fileReader)
{
    param1 = fileReader->get_uint32();
    param2 = fileReader->get_uint32();
}

void Instruction::Sub::read(std::shared_ptr<FileReaderBase> fileReader)
{
    param1 = fileReader->get_uint32();
    param2 = fileReader->get_uint32();
}

void Instruction::Mul::read(std::shared_ptr<FileReaderBase> fileReader)
{
    param1 = fileReader->get_uint32();
    param2 = fileReader->get_uint32();
}

void Instruction::Div::read(std::shared_ptr<FileReaderBase> fileReader)
{
    param1 = fileReader->get_uint32();
    param2 = fileReader->get_uint32();
}

void Instruction::Store::read(std::shared_ptr<FileReaderBase> fileReader)
{
    param1 = fileReader->get_uint32();
}

void Instruction::Compare::read(std::shared_ptr<FileReaderBase> fileReader)
{
    operand = static_cast<Instruction::Compare::CompareOperand>(fileReader->get_uint32());
    param1 = fileReader->get_uint32();
    param2 = fileReader->get_uint32();
}

void Instruction::Print::read(std::shared_ptr<FileReaderBase> fileReader)
{
    size = fileReader->get_uint32();
    printStr = fileReader->get_bytes(size);
}
