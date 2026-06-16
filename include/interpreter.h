#pragma once
#include "ringBuffer.h"
#include "instruction.h"
#include "global.h"
#include <stack>

class Interpreter
{
private:
    bool m_running { false };

protected:
    InstructionRingBuffer1024* m_ringBuffer { nullptr };
    std::stack<std::uint32_t> m_resultStack { };

public:
    Interpreter(InstructionRingBuffer1024* ringBuffer);
    virtual void run();
    virtual void stop();
};