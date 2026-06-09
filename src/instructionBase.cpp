#include "instructionBase.h"
#include "instruction.h"
#include <memory>


void InstructionBase::setFileReader(FileReader& target)
{            
    m_fileReader = target;
}

std::shared_ptr<Instruction::Base> InstructionBase::build()
{
    auto resInstruction = std::make_shared<Instruction::Base>(m_fileReader);
    auto resInstructionType = resInstruction->type;
    
    if (resInstructionType == 1)
    {
        resInstruction = std::make_shared<Instruction::Add>(m_fileReader);
    }
    
    return resInstruction;
}