#include <gtest/gtest.h>
#include "instructionBuilder.h"

TEST(InstructionBuilderCreationTest, StructsSuccessfullyCreated)
{
    char buffer[] = {0x01, 0x01, 0x02};
    FileReaderBase* testFileReaderBase = new BufferFileReader(buffer, 3);
    
    InstructionBuilder testInstructionBuilder(testFileReaderBase);
    
    auto resultInstruction = testInstructionBuilder.get_instruction();
    
    ASSERT_NE(resultInstruction, nullptr);
    ASSERT_EQ(resultInstruction->instructType, Instruction::InstructionType::ADD);

    switch (resultInstruction->instructType)
    {
        case Instruction::InstructionType::ADD :
        {
            std::shared_ptr<Instruction::Add> addInstruction = std::static_pointer_cast<Instruction::Add>(resultInstruction); 
            ASSERT_EQ(addInstruction->param1, 1);
            ASSERT_EQ(addInstruction->param2, 2);
            break;
        }
    }

}