#include <gtest/gtest.h>
#include "fileReader.h"

TEST(FileReaderInitializationTest, NoErrorThrownOnConstruction)
{
    FileReaderBase* testFileReader = new BufferFileReader(utils::makeFileStream("testData.txt"));

    ASSERT_EQ(testFileReader->get_uint32(), 1);
    ASSERT_EQ(testFileReader->get_uint32(), 2);
    ASSERT_EQ(testFileReader->get_uint32(), 3);
}