#pragma once
#include <cstdint>
#include "fileReader.h"

namespace Instruction
{
    // FIX -> return to integrate custom defined types
    // enum class InstructionType
    // {
    //     BASE = 0,
    //     ADD
    // };
    
    struct Base;
    struct Add;
}

struct Instruction::Base
{
    std::uint32_t type;

    Base();

    Base(FileReader& fileReader)
    {
        type = fileReader.read();
    }
};

struct Instruction::Add : public Instruction::Base
{
    std::uint32_t param1;
    std::uint32_t param2;

    Add(FileReader& fileReader)
    {
        //type = Instruction::InstructionType::ADD;
        type = 1;
        param1 = fileReader.read();
        param2 = fileReader.read();
    }
};