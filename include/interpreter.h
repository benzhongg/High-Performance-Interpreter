#pragma once
#include "ringBuffer.h"
#include "instruction.h"
#include <stack>

class Interpreter
{
private:
    // QUESTION -> What determines our ring buffer capacity? What are we bounded by? Heap memory?
    RingBuffer<Instruction::Base, 20>* m_ringBuffer;
    std::stack<Instruction::Base>* m_resultStack;

public:
    Interpreter();
    bool addInstruction(Instruction::Base inputInstruction);
    void run();
    void stop();
};