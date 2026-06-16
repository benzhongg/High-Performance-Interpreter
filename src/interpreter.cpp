#include "interpreter.h"
// CORRECTLY IDENTIFIED 
// #2, #3, #4, #5, #8, #9


// Issue #3 passing a ptr here is bad too should be a shared ptr since the buffer will also be used by injector
// Issue #5 -> ringBuffer parameter never actually assigned to our m_ringBuffer
Interpreter::Interpreter(InstructionRingBuffer1024* ringBuffer){}

// 4 issues originall. Revised -> "There are 7 issues total" - Gemini.
void Interpreter::run()
{
    m_running = true;

    while (m_running)
    {
        std::shared_ptr<Instruction::Base> instruction { nullptr };

        // Issue #2 this while loop would deadlock if m_running wasn't included, calling stop() wouldn't get change so we need to condition on m_running
        while(!m_ringBuffer->pop(instruction) && m_running)
        {
            std::this_thread::yield();
        }
        
        // Issue #8
        // if we stop() before we popped a value we're gonna access our instruction {nullptr} -> undefined behavior
        switch (instruction->instructType)
        {   
            case Instruction::InstructionType::ADD :
            {
                // we are downcasting an existing smart ptr to a derived class static cast is compile time optimal
                // Possibility-> read other casts
                auto addInstruction = static_cast<Instruction::Add*>(instruction.get());
                
                m_resultStack.push(addInstruction->param1 + addInstruction->param2);
                
                //issue #4
                // we need to end our cases or else we'll end up running through the next few cases
                continue;
            }
        }
    }
}

void Interpreter::stop()
{
    // Issue #9 we need to use synchronization tools here so that we don't have any concurrency issue between injectorThread and mainThread
    m_running = false;
}