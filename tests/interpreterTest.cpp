#include <gtest/gtest.h>
#include "interpreter.h"

TEST(ADDInstructionTest, ExecutingAddResultToStack)
{
    //inject and add 1, 2 to buffer
    //init interpreter
    ASSERT_EQ(Stack.pop(), 3);
}