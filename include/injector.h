#pragma once
#include "ringBuffer.h"
#include "fileReader.h"
#include "instruction.h"
#include "instructionBuilder.h"
#include <memory>
#include "global.h"
#include <thread>

class Injector
{
private:
    bool m_running { false };
    std::thread m_thread;

protected:
    std::shared_ptr<FileReaderBase> m_fileReader { nullptr };
    InstructionRingBuffer1KPtr m_ringBuffer { nullptr };
    std::unique_ptr<InstructionBuilder> m_instructBuilder { nullptr };

public:
    Injector(std::shared_ptr<FileReaderBase> fileReader, InstructionRingBuffer1KPtr buffer);
    
    virtual void run();
    virtual void runAsync();
    virtual void stop();
};