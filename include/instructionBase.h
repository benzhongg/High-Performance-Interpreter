#pragma once
#include "fileReader.h"
#include "instruction.h"
#include <memory>

class InstructionBase
{
public:
    InstructionBase() = default;

    std::shared_ptr<Instruction::Base> buildWithFileReader(FileReader& fileReader);

    std::shared_ptr<Instruction::Base> buildWithStream(std::istream& inputStream);
};