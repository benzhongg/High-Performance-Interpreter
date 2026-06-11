#include "instructionBuilder.h"
#include "instruction.h"
#include <memory>


std::shared_ptr<Instruction::Base> InstructionBuilder::get_instruction()
{
    Instruction::InstructionType type = static_cast<Instruction::InstructionType>(m_fileReader->get_uint32());
    
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
    }
    
    return nullptr;
}