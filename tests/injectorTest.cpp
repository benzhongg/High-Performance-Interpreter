#include <gtest/gtest.h>
#include "injector.h"

TEST(RunStopInjectorTest, OnNonEmptyBuffer)
{
    char buffer[] = {0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00};
    std::shared_ptr<FileReaderBase> testFileReader = std::make_shared<BufferFileReader>(buffer, 12);
    InstructionRingBuffer1KPtr testRingBuffer = std::make_shared<InstructionRingBuffer1024>();
    Injector testInjector(testFileReader, testRingBuffer);
    
    testInjector.runAsync();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    testInjector.stop();
    
    SUCCEED();
}


TEST(RunStopInjectorTest, OnFullBuffer)
{
    auto testStreamFileReader = StreamFileReader::create("fullBufferData.txt");
    auto testStreamFileReaderPtr = std::make_shared<StreamFileReader>(std::move(*testStreamFileReader));
    InstructionBuilder testInstructionBuilder = InstructionBuilder(testStreamFileReaderPtr);
    InstructionRingBuffer1KPtr testRingBuffer = std::make_shared<InstructionRingBuffer1024>();
    Injector testInjector(testStreamFileReaderPtr, testRingBuffer);
    testInjector.runAsync();
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    testInjector.stop();
    SUCCEED();
}