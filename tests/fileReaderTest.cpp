#include <gtest/gtest.h>
#include "fileReader.h"

TEST(InitializationTest, NoErrorThrownOnConstruction)
{
    FileReader test_FR;
    ASSERT_NO_THROW(test_FR.run(/*File*/));
}


TEST(fileReaderStopTest, CheckBoolean)
{
    FileReader test_FR;
    test_FR.run(/*input file*/);
    test_FR.stop();
    ASSERT_EQ(test_FR.isReading(), false);
}