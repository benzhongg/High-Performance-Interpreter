#include <gtest/gtest.h>
#include "instructionBuilder.h"

TEST(InstructionBuilderCreationTest, StructsSuccessfullyCreated)
{
    char buffer[] = {0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00};
    FileReaderBase* testFileReaderBase = new BufferFileReader(buffer, 12);
    InstructionBuilder testInstructionBuilder(testFileReaderBase);
    
    auto resInstruction = testInstructionBuilder.get_instruction();
    ASSERT_NE(resInstruction, nullptr);
    ASSERT_EQ(resInstruction->instructType, Instruction::InstructionType::ADD);

    switch (resInstruction->instructType)
    {
        case Instruction::InstructionType::ADD :
        {
            std::shared_ptr<Instruction::Add> addInstruction = std::static_pointer_cast<Instruction::Add>(resInstruction); 
            ASSERT_EQ(addInstruction->param1, 1);
            ASSERT_EQ(addInstruction->param2, 2);

    break;
        }
    }

}