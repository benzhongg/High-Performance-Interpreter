#include "instructionBuilder.h"
#include "instruction.h"
#include <memory>

std::shared_ptr<Instruction::Base> InstructionBuilder::get_instruction()
{
    auto baseInstruction = std::make_shared<Instruction::Base>();
    baseInstruction->read(m_fileReader);
    
    switch(baseInstruction->instructType)
    {
        case Instruction::ADD :
        {
            baseInstruction = std::make_shared<Instruction::Add>();
            break;
        }
        
        case Instruction::SUB :
        {
            baseInstruction = std::make_shared<Instruction::Sub>();
            break;
        }
        
        case Instruction::MUL :
        {
            baseInstruction = std::make_shared<Instruction::Mul>();
            break;
        }
        
        case Instruction::DIV :
        {
            baseInstruction = std::make_shared<Instruction::Div>();
            break;
        }
        
        case Instruction::STORE :
        {
            baseInstruction = std::make_shared<Instruction::Store>();
            break;
        }
        
        case Instruction::CMP :
        {
            baseInstruction = std::make_shared<Instruction::Compare>();
            break;
        }
        
        case Instruction::PRINT :
        {
            baseInstruction = std::make_shared<Instruction::Print>();
            break;
        }

        default :
        {
            return nullptr;
        }
    }
    
    baseInstruction->read(m_fileReader);

    return baseInstruction;
}