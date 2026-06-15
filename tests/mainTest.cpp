#include <gtest/gtest.h>
#include "instructionBuilder.h"
#include "injector.h"
#include "interpreter.h"
#include "fileReader.h"
#include "stream_utils.h"
#include <thread>

TEST(mainTest, ModulesSuccessfullyCreated)
{
    FileReaderBase* testFileReader = new BufferFileReader(utils::makeFileStream("testData.txt"));
    InstructionBuilder testInstructionBuilder(testFileReader);
    RingBuffer<std::shared_ptr<Instruction::Base>, 1024>* testBuffer = new RingBuffer<std::shared_ptr<Instruction::Base>, 1024>();
    
    Injector testInjector(testFileReader, testBuffer);
    Interpreter testInterpreter(testBuffer);

    std::thread threadA(&Injector::run, &testInjector);
}