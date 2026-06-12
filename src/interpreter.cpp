#include "interpreter.h"

Interpreter::Interpreter(RingBuffer<std::shared_ptr<Instruction::Base>,1024>* ringBuffer)
{

}

void Interpreter::run()
{
    // when you develop a run function in a thread you'll usually need a super loop

    while (true)
    {
        //grabs from ringbuffer
        //the instance of the shared ptr is a non ptr / regular variable
        std::shared_ptr<Instruction::Base> instruction { nullptr };

        while(!m_ringBuffer->pop(instruction))
        {
            std::this_thread::yield();
        }
        
        //executes instruction 
        switch (instruction->instructType)
        {
            case Instruction::InstructionType::ADD :
            {
                auto addInstruction = static_cast<Instruction::Add*>(instruction.get());
                
                // std::uint32_t instructionResult { addInstruction->param1 + addInstruction->param2 } ;
                // m_resultStack.push(instructionResult);
            
                //pushes to stack 
                m_resultStack.push(addInstruction->param1 + addInstruction->param2);
            }
        }
    }
}