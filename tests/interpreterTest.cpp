#include <gtest/gtest.h>
#include "interpreter.h"
#include "instructionBuilder.h"
#include "ringBuffer.h"
#include "injector.h"
#include "global.h"
//create macro
    //clutter
    //hard to debug cannot be stepped into -> debugging the binary file 
//create static function 
    // runSetup(buffer[])
//create mock class
    // class::create(buffer[])
class MockVM
{
private:

    BufferFileReader m_testBufferFileReader;
    InstructionRingBuffer1KPtr testRingBufferPtr = std::make_shared<InstructionRingBuffer1024>();

    

public:
    MockVM(char* buffer, size_t size)
    {
        m_testBufferFileReader = BufferFileReader(buffer, size);
    }
    
    
    bool evaluateStack(std::uint32_t expectedValue)
    {
        return m_resultStack.top() == expectedValue;
    }
};

// change definition of the mockclass
TEST(AddInstructionTest, ExecutingAddFromBuffer)
{
    char bufferWithAddInstruction[] = {0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00};
    MockVM testMVM(buffer, size);
    testMVM.run();
    ASSERT_EQ(testInterpreter.evaluateStack(5), true);
}

// TEST(SubInstructionTest, ExecutingSubFromBuffer)
// {
//     char bufferWithSubInstruction[] = {0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00};
    
//     FileReaderBase* testBufferFileReaderPtr = new BufferFileReader(bufferWithSubInstruction, 12);
//     InstructionRingBuffer1KPtr testRingBufferPtr = std::make_shared<InstructionRingBuffer1024>();

//     Injector testInjector(testBufferFileReaderPtr, testRingBufferPtr);
//     Interpreter testInterpreter(testRingBufferPtr);

//     std::thread threadInjector(&Injector::run, &testInjector);
//     std::thread threadInterpreter(&Interpreter::run, &testInterpreter);

//     std::this_thread::sleep_for(std::chrono::milliseconds(1000));

//     testInjector.stop();
//     testInterpreter.stop();

//     threadInjector.join();
//     threadInterpreter.join();
//     ASSERT_EQ(testInterpreter.m_resultStack.top(), 1);
// }

// TEST(MulInstructionTest, ExecutingMulFromBuffer)
// {
//     char bufferWithSubInstruction[] = {0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00};
    
//     FileReaderBase* testBufferFileReaderPtr = new BufferFileReader(bufferWithSubInstruction, 12);
//     InstructionRingBuffer1KPtr testRingBufferPtr = std::make_shared<InstructionRingBuffer1024>();

//     Injector testInjector(testBufferFileReaderPtr, testRingBufferPtr);
//     Interpreter testInterpreter(testRingBufferPtr);

//     std::thread threadInjector(&Injector::run, &testInjector);
//     std::thread threadInterpreter(&Interpreter::run, &testInterpreter);

//     std::this_thread::sleep_for(std::chrono::milliseconds(1000));

//     testInjector.stop();
//     testInterpreter.stop();

//     threadInjector.join();
//     threadInterpreter.join();
//     ASSERT_EQ(testInterpreter.m_resultStack.top(), 6);
// }

// TEST(DivInstructionTest, ExecutingDivFromBuffer)
// {
//     char bufferWithDivInstruction[] = {0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00};
    
//     FileReaderBase* testBufferFileReaderPtr = new BufferFileReader(bufferWithDivInstruction, 12);
//     InstructionRingBuffer1KPtr testRingBufferPtr = std::make_shared<InstructionRingBuffer1024>();

//     Injector testInjector(testBufferFileReaderPtr, testRingBufferPtr);
//     Interpreter testInterpreter(testRingBufferPtr);

//     std::thread threadInjector(&Injector::run, &testInjector);
//     std::thread threadInterpreter(&Interpreter::run, &testInterpreter);

//     std::this_thread::sleep_for(std::chrono::milliseconds(1000));

//     testInjector.stop();
//     testInterpreter.stop();

//     threadInjector.join();
//     threadInterpreter.join();
//     ASSERT_EQ(testInterpreter.m_resultStack.top(), 2);
// }

// TEST(StoreInstructionTest, ExecutingStoreFromBuffer)
// {
//     char bufferWithStoreInstruction[] = {0x05, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00};
    
//     FileReaderBase* testBufferFileReaderPtr = new BufferFileReader(bufferWithStoreInstruction, 8);
//     InstructionRingBuffer1KPtr testRingBufferPtr = std::make_shared<InstructionRingBuffer1024>();

//     Injector testInjector(testBufferFileReaderPtr, testRingBufferPtr);
//     Interpreter testInterpreter(testRingBufferPtr);

//     std::thread threadInjector(&Injector::run, &testInjector);
//     std::thread threadInterpreter(&Interpreter::run, &testInterpreter);

//     std::this_thread::sleep_for(std::chrono::milliseconds(1000));

//     testInjector.stop();
//     testInterpreter.stop();

//     threadInjector.join();
//     threadInterpreter.join();
//     ASSERT_EQ(testInterpreter.m_resultStack.top(), 5);
// }

// TEST(CompareInstructionTest, ExecutingCompareFromBuffer)
// {
//     char bufferWithCompareInstruction[] = {0x06, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00};
    
//     FileReaderBase* testBufferFileReaderPtr = new BufferFileReader(bufferWithCompareInstruction, 12);
//     InstructionRingBuffer1KPtr testRingBufferPtr = std::make_shared<InstructionRingBuffer1024>();

//     Injector testInjector(testBufferFileReaderPtr, testRingBufferPtr);
//     Interpreter testInterpreter(testRingBufferPtr);

//     std::thread threadInjector(&Injector::run, &testInjector);
//     std::thread threadInterpreter(&Interpreter::run, &testInterpreter);

//     std::this_thread::sleep_for(std::chrono::milliseconds(1000));

//     testInjector.stop();
//     testInterpreter.stop();

//     threadInjector.join();
//     threadInterpreter.join();
//     ASSERT_EQ(testInterpreter.m_resultStack.top(), 1);
// }

// TEST(PrintInstructionTest, ExecutingPrintFromBuffer)
// {
//     char bufferWithPrintInstruction[] = {0x09, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 'h', 'e', 'l', 'l', 'o','w','o','r','l','d'};
//     FileReaderBase* testFileReader = new BufferFileReader(bufferWithPrintInstruction, 18);
//     InstructionRingBuffer1KPtr testRingBuffer = std::make_shared<InstructionRingBuffer1024>();

//     Injector testInjector(testFileReader, testRingBuffer);
//     Interpreter testInterpreter(testRingBuffer);
    
//     std::thread threadInjector(&Injector::run, &testInjector);
//     std::thread threadInterpreter(&Interpreter::run, &testInterpreter);
    
//     std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
//     testInjector.stop();
//     testInterpreter.stop();
    
//     threadInjector.join();
//     threadInterpreter.join();
// }