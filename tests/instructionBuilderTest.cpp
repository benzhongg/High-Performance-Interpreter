#include <gtest/gtest.h>
#include "instructionBuilder.h"
#include "injector.h"
#include "interpreter.h"
#include "fileReader.h"

TEST(InstructionBuilderCreationTest, StructsSuccessfullyCreated)
{
    char buffer[] = {0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00};
    FileReaderBase* testFileReader =  new BufferFileReader(buffer, 12);
    
    InstructionBuilder testInstructionBuilder(testFileReader);
    RingBuffer<std::shared_ptr<Instruction::Base>, 1024>* testBuffer = new RingBuffer<std::shared_ptr<Instruction::Base>, 1024>();
    
    Injector testInjector(testFileReader, testBuffer);
    testInjector.run(std::stop_thread stopThread);

    // Interpreter testInterpreter(testBuffer);
    // testInterpreter.run();


}