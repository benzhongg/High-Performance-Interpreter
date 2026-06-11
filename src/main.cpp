#include <iostream>
#include "instructionBuilder.h"

int main()
{
    char buffer[] = {0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00};
    FileReaderBase* testFileReaderBase = new BufferFileReader(buffer, 12);
    InstructionBuilder testInstructionBuilder(testFileReaderBase);
    
    auto resInstruction = testInstructionBuilder.get_instruction();
    switch (resInstruction->instructType)
    {
        case Instruction::ADD :
        {
            // error inducing line 
            // auto addInstruction = static_cast<Instruction::Add*>(resInstruction.get());
            // Instruction::InstructionType resType;
            // ASSERT_EQ(resInstruction, nullptr);
            // ASSERT_EQ(resInstruction->type, Instruction::InstructionType::ADD);
            // std::cout << 1 << std::endl;
            std::shared_ptr<Instruction::Add> addInstruction = std::static_pointer_cast<Instruction::Add>(resInstruction); 
    //         // ASSERT_EQ(addInstruction->param1, 2);
    //         // ASSERT_EQ(addInstruction->param2, 3);
        }
    }
}
