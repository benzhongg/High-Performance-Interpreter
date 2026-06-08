#include <gtest/gtest.h>
#include "instructionBuilder.h"

TEST(AddInstructionTest, CorrectValues)
{
    AddBuilder test_AB;
    Instruction::ADD* test_add_instruction = test_AB.create();
}