#pragma once
#include <cstdint>
#include "fileReader.h"
#include <iostream>
#include <string>

namespace Instruction
{
    using InstructionType = std::uint32_t;
    struct Base;
    struct Add;
}

struct Instruction::Base
{
    InstructionType type;

    Base(InstructionType instructionType) : type (instructionType){};
};

struct Instruction::Add : public Instruction::Base
{
    std::uint32_t param1;
    std::uint32_t param2;

    Add(FileReader& fileReader, InstructionType t) : Base(t)
    {
        param1 = fileReader.read();
        param2 = fileReader.read();
    }

    Add(std::istream& inputStream, InstructionType t) : Base(t)
    {
        type = 1;
        inputStream >> param1;
        inputStream >> param2;
    }

};