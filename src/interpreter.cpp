#include "interpreter.h"

Interpreter::Interpreter(RingBuffer<std::shared_ptr<Instruction::Base>,1024>* ringBuffer)
{

}

void Interpreter::run()
{
    while (true)
    {
        std::shared_ptr<Instruction::Base> instruction { nullptr };

        while(!m_ringBuffer->pop(instruction))
        {
            std::this_thread::yield();
        }
        
        switch (instruction->instructType)
        {
            case Instruction::InstructionType::ADD :
            {
                auto addInstruction = static_cast<Instruction::Add*>(instruction.get());
                
                m_resultStack.push(addInstruction->param1 + addInstruction->param2);
                std::cout << "pushing to stack succeeded\n";
            }
        }
    }
}

void Interpreter::stop()
{

}