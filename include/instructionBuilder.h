#pragma once
#include "fileReader.h"
#include "instruction.h"
#include <memory>

//instruction builder 
class InstructionBuilder
{

private: 
    FileReaderBase* m_fileReader = nullptr;

public:
    InstructionBuilder() = default;

    InstructionBuilder(FileReaderBase* target) : m_fileReader(target) {};

    std::shared_ptr<Instruction::Base> get_instruction();
};