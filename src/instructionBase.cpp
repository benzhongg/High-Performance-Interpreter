#include "instructionBase.h"
#include "instruction.h"
#include <memory>

void InstructionBase::setFileReader(FileReader& target)
{            
    m_fileReader = target;
}

// std::shared_ptr<Instruction::Base> InstructionBase::build()
// {
//     Instruction::InstructionType type;

//     if (!(inputStream >> type)) return nullptr;

//     auto resInstructionType = resInstruction->type;
    
//     if (resInstructionType == 1)
//     {
//         resInstruction = std::make_shared<Instruction::Add>(m_fileReader, type);
//     }
    
//     return resInstruction;
// }

std::shared_ptr<Instruction::Base> InstructionBase::buildWithStream(std::istream& inputStream)
{
    Instruction::InstructionType type;

    if (!(inputStream >> type)) return nullptr;
    
    switch(type)
    {
        case 1:
            return std::make_shared<Instruction::Add>(inputStream, type);
    }

    return nullptr;
}