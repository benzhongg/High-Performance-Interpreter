#include "instructionBuilder.h"
#include "instruction.h"
#include <memory>

std::shared_ptr<Instruction::Base> InstructionBuilder::get_instruction()
{
    Instruction::Base baseInstruction;
    baseInstruction.read(m_fileReader);
    
    switch(baseInstruction.instructType)
    {
        case Instruction::ADD :
        {
            auto baseInstruction = std::make_shared<Instruction::Add>();
            baseInstruction->read(m_fileReader);
            
            return baseInstruction;
        }
        
        case Instruction::SUB :
        {
            auto baseInstruction = std::make_shared<Instruction::Sub>();
            baseInstruction->read(m_fileReader);

            return baseInstruction;
        }
        
        case Instruction::MUL :
        {
            auto baseInstruction = std::make_shared<Instruction::Mul>();
            baseInstruction->read(m_fileReader);

            return baseInstruction;
        }
        
        case Instruction::DIV :
        {
            auto baseInstruction = std::make_shared<Instruction::Div>();
            baseInstruction->read(m_fileReader);

            return baseInstruction;
        }
        
        case Instruction::STORE :
        {
            auto baseInstruction = std::make_shared<Instruction::Store>();
            baseInstruction->read(m_fileReader);

            return baseInstruction;
        }
        
        case Instruction::CMP :
        {
            auto baseInstruction = std::make_shared<Instruction::Compare>();
            baseInstruction->read(m_fileReader);

            return baseInstruction;
        }
        
        case Instruction::PRINT :
        {
            auto printInstruction = std::make_shared<Instruction::Print>();
            printInstruction->read(m_fileReader);

            return printInstruction;
        }
    }
    
    return nullptr;
}