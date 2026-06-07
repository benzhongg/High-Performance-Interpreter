#include <gtest/gtest.h>
#include "instruction.h"

TEST(BaseInstructionCreationTest, CorrectValues)
{
    Instruction::Base test_base_instruct();
    ASSERT_EQ(test_base_instruct.id(), 0);
    ASSERT_EQ(test_base_instruct.type, Instruction::Types::Base);
}

TEST(ADDInstructionCreationTests, CorrectValues)
{
    Instruction::ADD test_add();
    ASSERT_EQ(test_add.id(), 1);
    ASSERT_EQ(test_add.type, Instruction::Types::Add);
    std::array<int, 2> test_contents = {1, 1};
    ASSERT_EQ(test_add.operand, test_contents);
}