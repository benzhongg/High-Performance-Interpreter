#include <gtest/gtest.h>
#include "injector.h"

TEST(CreateAndRunTest, AcceptsFileAndRingBuffer)
{
    Injector test_injector(/*File and RingBuffer*/);
    SUCCEED();
}


TEST(InjectInstructionTest, InstructionInRingBuffer)
{
    //success if instruction is passed to ringbuffer
    SUCCEED();
}


TEST(StopTest, SuccessfulStop)
{
    Injector test_injector();
    test_injector.stop();
    SUCCEED();
}