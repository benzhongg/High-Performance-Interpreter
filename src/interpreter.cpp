#include "interpreter.h"
Interpreter::Interpreter(std::shared_ptr<InstructionRingBuffer1024> targetRingBuffer) : m_ringBuffer(targetRingBuffer) {}

void Interpreter::run()
{
    m_running.store(true, std::memory_order_release);

    while (m_running.load(std::memory_order_acquire))
    {
        // Possible Issue 
        // We're inputting base object ptrs and getting derived obj ptrs back 
        std::shared_ptr<Instruction::Base> instruction { nullptr };

        while(!m_ringBuffer->pop(instruction) && m_running.load(std::memory_order_acquire))
        {
            std::this_thread::yield();
        }
        
        if (!m_running.load(std::memory_order_acquire)) { break; }

        switch (instruction->instructType)
        {   
            case Instruction::InstructionType::ADD :
            {
                // Possible Issue
                // we are downcasting an existing smart ptr to a derived class
                // if this fails we have Undefined behavior
                auto addInstruction = static_cast<Instruction::Add*>(instruction.get());
                
                m_resultStack.push(addInstruction->param1 + addInstruction->param2);
                
                // choosing break over continue so that we can read the code better
                // break leaves the switch statement -> 1 manual exit then let while loop end naturally
                // continue leaves the current while loop iteration -> 2 manual exits 
                break;
            }
        }
    }
}

void Interpreter::stop()
{
    m_running.store(false, std::memory_order_release);
}