#include <gtest/gtest.h>
#include "fileReader.h"

TEST(TestStreamReader, ValidFilePath)
{
    auto testStreamReader = StreamFileReader::create("testData.txt");

    ASSERT_TRUE(testStreamReader);
}

TEST(TestStreamReader, InvalidFilePath)
{
    auto testStreamReader = StreamFileReader::create("");
    ASSERT_FALSE(testStreamReader);
    ASSERT_EQ(testStreamReader.error(), ErrorCode::InvalidFormat);
}

TEST(TestStreamReader, ValidFileFormat)
{
    auto testStreamReader = StreamFileReader::create("testData.txt");
    ASSERT_TRUE(testStreamReader);
}

TEST(TestStreamReader, InvalidFileFormat)
{
    auto testStreamReader = StreamFileReader::create("testData.html");
    ASSERT_FALSE(testStreamReader);
    ASSERT_EQ(testStreamReader.error(), ErrorCode::InvalidFormat);
}

TEST(TestStreamReader, EmptyFile)
{

}

TEST(TestStreamReader, ValidCode)
{

}

TEST(TestStreamReader, InvalidCode)
{

}
