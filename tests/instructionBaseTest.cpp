#include <gtest/gtest.h>
#include "instructionBase.h"

TEST(InstructionBaseCreationTest, StructsSuccessfullyCreated)
{
    std::stringstream testStream("1 2 3");
    InstructionBase testInstructionBase;
    
    auto resInstruction = testInstructionBase.buildWithStream(testStream);
    auto resAdd = std::static_pointer_cast<Instruction::Add>(resInstruction);
    
    ASSERT_EQ(resInstruction->type, 1);
    ASSERT_EQ(resAdd->param1, 2);
    ASSERT_EQ(resAdd->param2, 3);

}