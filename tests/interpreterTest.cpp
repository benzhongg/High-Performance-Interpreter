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

TEST(AddInstructionTest, withCharBuffer)
{
    const char bufferContainingAdd[] = {0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00};
    MockVM testInstance(bufferContainingAdd, 12);
    testInstance.run();
    ASSERT_EQ(testInstance.resultCheck(5), true);
}

TEST(SubInstructionTest, withCharBuffer)
{
    char bufferContainingSub[] = {0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00};
    MockVM testInstance(bufferContainingSub, 12);
    testInstance.run();
    ASSERT_EQ(testInstance.resultCheck(1), true);
}

TEST(MulInstructionTest, withCharBuffer)
{
    char bufferContainingMul[] = {0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00};
    MockVM testInstance(bufferContainingMul, 12);
    testInstance.run();
    ASSERT_EQ(testInstance.resultCheck(6), true);
}

TEST(DivInstructionTest, withCharBuffer)
{
    char bufferContainingDiv[] = {0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00};
    MockVM testInstance(bufferContainingDiv, 12);
    testInstance.run();
    ASSERT_EQ(testInstance.resultCheck(2), true);
}

TEST(StoreInstructionTest, withCharBuffer)
{
    char bufferContainingStore[] = {0x05, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00};
    MockVM testInstance(bufferContainingStore, 8);
    testInstance.run();
    ASSERT_EQ(testInstance.resultCheck(5), true);
}

TEST(GTCompareInstructionTest, withCharBufferTrueOutput)
{
    char bufferContainingCompare[] = {0x06, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00};
    MockVM testInstance(bufferContainingCompare, 16);
    testInstance.run();
    ASSERT_EQ(testInstance.resultCheck(1), true);
}

TEST(GTCompareInstructionTest, withCharBufferFalseOutput)
{
    char bufferContainingCompare[] = {0x06, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00};
    MockVM testInstance(bufferContainingCompare, 16);
    testInstance.run();
    ASSERT_EQ(testInstance.resultCheck(0), true);
}

TEST(LTCompareInstructionTest, withCharBufferTrueOutput)
{
    char bufferContainingCompare[] = {0x06, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00};
    MockVM testInstance(bufferContainingCompare, 16);
    testInstance.run();
    ASSERT_EQ(testInstance.resultCheck(1), true);
}

TEST(LTCompareInstanceTest, withCharBufferFalseOutput)
{
    char bufferContainingCompare[] = {0x06, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00};
    MockVM testInstance(bufferContainingCompare, 16);
    testInstance.run();
    ASSERT_EQ(testInstance.resultCheck(0), true);
}

//GTE TRUE + FALSE
TEST(GTECompareInstructionTest, withCharBufferTrueOutput)
{
    char bufferContainingCompare[] = {0x06, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00};
    MockVM testInstance(bufferContainingCompare, 16);
    testInstance.run();
    ASSERT_EQ(testInstance.resultCheck(1), true);
}

TEST(GTECompareInstructionTest, withCharBufferFalseOutput)
{
    char bufferContainingCompare[] = {0x06, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00};
    MockVM testInstance(bufferContainingCompare, 16);
    testInstance.run();
    ASSERT_EQ(testInstance.resultCheck(0), true);
}

//LTE TRUE + FALSE
TEST(LTECompareInstructionTest, withCharBufferTrueOutput)
{
    char bufferContainingCompare[] = {0x06, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00};
    MockVM testInstance(bufferContainingCompare, 16);
    testInstance.run();
    ASSERT_EQ(testInstance.resultCheck(1), true);
}

TEST(LTECompareInstructionTest, withCharBufferFalseOutput)
{
    char bufferContainingCompare[] = {0x06, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00};
    MockVM testInstance(bufferContainingCompare, 16);
    testInstance.run();
    ASSERT_EQ(testInstance.resultCheck(0), true);
}

//EQ TRUE + FALSE
TEST(EQCompareInstructionTest, withCharBufferTrueOutput)
{
    char bufferContainingCompare[] = {0x06, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00};
    MockVM testInstance(bufferContainingCompare, 16);
    testInstance.run();
    ASSERT_EQ(testInstance.resultCheck(1), true);
}

TEST(EQCompareInstructionTest, withCharBufferFalseOutput)
{
    char bufferContainingCompare[] = {0x06, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00};
    MockVM testInstance(bufferContainingCompare, 16);
    testInstance.run();
    ASSERT_EQ(testInstance.resultCheck(0), true);
}