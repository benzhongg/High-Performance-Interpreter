#include <gtest/gtest.h>
#include "fileReader.h"
#include "instructionBuilder.h"

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
    auto testStreamReader = StreamFileReader::create("testEmptyData.txt");
    if (testStreamReader)
    {
        auto testStreamReaderPtr = std::make_shared<StreamFileReader>(std::move(*testStreamReader));
        InstructionBuilder testInstructionBuilder = InstructionBuilder(testStreamReaderPtr);
        ASSERT_THROW(testInstructionBuilder.get_instruction(), std::runtime_error);
    } 
}

TEST(TestStreamReader, ValidBinaryDataPassing)
{
    auto testStreamReader = StreamFileReader::create("testData.txt");
    if (testStreamReader)
    {
        auto testStreamReaderPtr = std::make_shared<StreamFileReader>(std::move(*testStreamReader));
        InstructionBuilder testInstructionBuilder = InstructionBuilder(testStreamReaderPtr);
        auto res = testInstructionBuilder.get_instruction();
        ASSERT_EQ(res->instructType, Instruction::InstructionType::ADD);
    }
}