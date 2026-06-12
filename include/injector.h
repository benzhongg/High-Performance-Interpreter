#pragma once
#include "ringBuffer.h"
#include "fileReader.h"
#include "instruction.h"
#include "instructionBuilder.h"
#include "memory"

class Injector
{
protected:
    FileReaderBase* m_fileReader { nullptr };
    RingBuffer<std::shared_ptr<Instruction::Base>, 1024>* m_ringBuffer { nullptr };
    InstructionBuilder* m_instructBuilder { nullptr };

public:
    Injector(FileReaderBase* fileReader, RingBuffer<std::shared_ptr<Instruction::Base>, 1024>* buffer);
    virtual void run();
    virtual void stop();
};




