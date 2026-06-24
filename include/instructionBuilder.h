#pragma once
#include "fileReader.h"
#include "instruction.h"
#include <memory>

class InstructionBuilder
{

private: 
    std::shared_ptr<FileReaderBase> m_fileReader { nullptr };

public:
    InstructionBuilder() = default;

    InstructionBuilder(std::shared_ptr<FileReaderBase> target) : m_fileReader(target) {};

    std::shared_ptr<Instruction::Base> get_instruction();
};