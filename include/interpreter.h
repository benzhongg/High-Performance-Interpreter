#pragma once
#include "ringBuffer.h"
#include "instruction.h"
#include "global.h"
#include <stack>

class Interpreter
{
private:
    std::atomic<bool> m_running { false };
    std::thread m_thread;
    
protected:
    InstructionRingBuffer1KPtr m_ringBuffer { nullptr };
    std::stack<std::uint32_t> m_resultStack { };

public:
    Interpreter(InstructionRingBuffer1KPtr ringBuffer);
    virtual void run();
    virtual void runAsync();
    virtual void stop();
};