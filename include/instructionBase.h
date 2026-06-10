#pragma once
#include "fileReader.h"
#include "instruction.h"
#include <memory>

class InstructionBase
{
private:
    // FIX -> ref initalized no default value error
    // DO NOT FORGET TO TURN THIS BACK TO A REFERENCE
    FileReader m_fileReader;
public:
    InstructionBase() = default;
    
    void setFileReader(FileReader& target);

    // std::shared_ptr<Instruction::Base> build();

    std::shared_ptr<Instruction::Base> buildWithStream(std::istream& inputStream);
};