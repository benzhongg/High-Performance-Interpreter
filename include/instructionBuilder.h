#pragma once
#include "instruction.h"
#include <memory>
#include "instructionBase.h"

class InstructionBuilder
{
private:
    // FIX -> No default values. is a reference is the correct place here
    FileReader& m_fileReader;
    InstructionBase m_instructionBase;

public:
    InstructionBuilder(FileReader& fileReader) : m_fileReader(fileReader){};
    std::shared_ptr<Instruction::Base> getInstruction();
};