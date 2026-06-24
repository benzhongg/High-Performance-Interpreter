#include <gtest/gtest.h>
#include "interpreter.h"
#include "instructionBuilder.h"
#include "ringBuffer.h"
#include "injector.h"
#include "global.h"
class MockVM
{
private:
    class MockInterpreter : public Interpreter
    {
    public:
        MockInterpreter(InstructionRingBuffer1KPtr ringBufferPtrInput) : Interpreter(ringBufferPtrInput){};

        bool verifyStack(std::uint32_t testValue)
        {
            return m_resultStack.top() == testValue;
        }
    };

    std::shared_ptr<FileReaderBase> m_fileReader { nullptr };
    InstructionRingBuffer1KPtr m_ringBufferPtr = std::make_shared<InstructionRingBuffer1024>();
    Injector m_injector = Injector(m_fileReader, m_ringBufferPtr);
    MockInterpreter m_interpreter = MockInterpreter(m_ringBufferPtr);


public:
    MockVM(const char* buffer, size_t size)
    {
        m_fileReader = std::make_shared<BufferFileReader>(buffer, size);
        m_injector = Injector(m_fileReader, m_ringBufferPtr);
    }
    
    void run()
    {
        m_injector.runAsync();
        m_interpreter.runAsync();

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        m_injector.stop();
        m_interpreter.stop();
    }
    
    bool resultCheck(std::uint32_t expectedValue)
    {
        return m_interpreter.verifyStack(expectedValue);
    }
};

TEST(AddInterpreterTest, withCharBuffer)
{
    const char bufferContainingAdd[] = {0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00};
    MockVM testInstance(bufferContainingAdd, 12);
    testInstance.run();
    ASSERT_EQ(testInstance.resultCheck(5), true);
}

TEST(SubInterpreterTest, withCharBuffer)
{
    char bufferContainingSub[] = {0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00};
    MockVM testInstance(bufferContainingSub, 12);
    testInstance.run();
    ASSERT_EQ(testInstance.resultCheck(1), true);
}

TEST(MulInterpreterTest, withCharBuffer)
{
    char bufferContainingMul[] = {0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00};
    MockVM testInstance(bufferContainingMul, 12);
    testInstance.run();
    ASSERT_EQ(testInstance.resultCheck(6), true);
}

TEST(DivInterpreterTest, withCharBuffer)
{
    char bufferContainingDiv[] = {0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00};
    MockVM testInstance(bufferContainingDiv, 12);
    testInstance.run();
    ASSERT_EQ(testInstance.resultCheck(2), true);
}

TEST(StoreInterpreterTest, withCharBuffer)
{
    char bufferContainingStore[] = {0x05, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00};
    MockVM testInstance(bufferContainingStore, 8);
    testInstance.run();
    ASSERT_EQ(testInstance.resultCheck(5), true);
}

TEST(GTCompareInterpreterTest, withCharBufferTrueOutput)
{
    char bufferContainingCompare[] = {0x06, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00};
    MockVM testInstance(bufferContainingCompare, 16);
    testInstance.run();
    ASSERT_EQ(testInstance.resultCheck(1), true);
}

TEST(GTCompareInterpreterTest, withCharBufferFalseOutput)
{
    char bufferContainingCompare[] = {0x06, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00};
    MockVM testInstance(bufferContainingCompare, 16);
    testInstance.run();
    ASSERT_EQ(testInstance.resultCheck(0), true);
}

TEST(LTCompareInterpreterTest, withCharBufferTrueOutput)
{
    char bufferContainingCompare[] = {0x06, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00};
    MockVM testInstance(bufferContainingCompare, 16);
    testInstance.run();
    ASSERT_EQ(testInstance.resultCheck(1), true);
}

TEST(LTCompareInterpreterTest, withCharBufferFalseOutput)
{
    char bufferContainingCompare[] = {0x06, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00};
    MockVM testInstance(bufferContainingCompare, 16);
    testInstance.run();
    ASSERT_EQ(testInstance.resultCheck(0), true);
}

TEST(GTECompareInterpreterTest, withCharBufferTrueOutput)
{
    char bufferContainingCompare[] = {0x06, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00};
    MockVM testInstance(bufferContainingCompare, 16);
    testInstance.run();
    ASSERT_EQ(testInstance.resultCheck(1), true);
}

TEST(GTECompareInterpreterTest, withCharBufferFalseOutput)
{
    char bufferContainingCompare[] = {0x06, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00};
    MockVM testInstance(bufferContainingCompare, 16);
    testInstance.run();
    ASSERT_EQ(testInstance.resultCheck(0), true);
}

TEST(LTECompareInterpreterTest, withCharBufferTrueOutput)
{
    char bufferContainingCompare[] = {0x06, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00};
    MockVM testInstance(bufferContainingCompare, 16);
    testInstance.run();
    ASSERT_EQ(testInstance.resultCheck(1), true);
}

TEST(LTECompareInterpreterTest, withCharBufferFalseOutput)
{
    char bufferContainingCompare[] = {0x06, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00};
    MockVM testInstance(bufferContainingCompare, 16);
    testInstance.run();
    ASSERT_EQ(testInstance.resultCheck(0), true);
}

TEST(EQCompareInterpreterTest, withCharBufferTrueOutput)
{
    char bufferContainingCompare[] = {0x06, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00};
    MockVM testInstance(bufferContainingCompare, 16);
    testInstance.run();
    ASSERT_EQ(testInstance.resultCheck(1), true);
}

TEST(EQCompareInterpreterTest, withCharBufferFalseOutput)
{
    char bufferContainingCompare[] = {0x06, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00};
    MockVM testInstance(bufferContainingCompare, 16);
    testInstance.run();
    ASSERT_EQ(testInstance.resultCheck(0), true);
}

TEST(PrintInterpreterTest, withCharBuffer)
{
    char bufferContainingPrint[] = {0x07, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x68, 0x65, 0x6C, 0x6F, 0x77, 0x6F, 0x72, 0x6C, 0x64};
    MockVM testInstance(bufferContainingPrint, 18);
    testInstance.run();
    SUCCEED();
}