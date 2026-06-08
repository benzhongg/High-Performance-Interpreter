#pragma once
#include "instruction.h"

class InstructionBuilder
{
    public:
        InstructionBuilder();
        // covariant return type
        virtual Instruction::Base* create() = 0;
        virtual ~InstructionBuilder() = default;
};


class AddBuilder : public InstructionBuilder
{
    Instruction::ADD* create() override;
};