#pragma once
#include "fileReader.h"
#include "instruction.h"
#include <memory>

class InstructionBase
{
private:
    // FIX -> ref initalized no default value error
    FileReader& m_fileReader;
public:
    InstructionBase() = default;

    void setFileReader(FileReader& target);

    std::shared_ptr<Instruction::Base> build();
};