#pragma once
#include "ringBuffer.h"
#include "instruction.h"
#include <stack>

class Interpreter
{
protected:
    RingBuffer<std::shared_ptr<Instruction::Base>, 1024>* m_ringBuffer { nullptr };
    std::stack<std::uint32_t> m_resultStack { };

public:
    Interpreter(RingBuffer<std::shared_ptr<Instruction::Base>,1024>* ringBuffer);
    virtual void run();
    virtual void stop();
};