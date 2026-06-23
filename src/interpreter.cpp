#include "interpreter.h"
Interpreter::Interpreter(InstructionRingBuffer1KPtr targetRingBuffer) : m_ringBuffer(targetRingBuffer) {}

void Interpreter::runAsync()
{
    m_thread = std::thread(&Interpreter::run, this);
}

void Interpreter::run()
{
    m_running.store(true, std::memory_order_release);

    while (m_running.load(std::memory_order_acquire))
    {
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
                auto addInstruction = static_cast<Instruction::Add*>(instruction.get());
                m_resultStack.push(addInstruction->param1 + addInstruction->param2);
                break;
            }

            case Instruction::InstructionType::SUB :
            {
                auto subInstruction = static_cast<Instruction::Sub*>(instruction.get());
                m_resultStack.push(subInstruction->param1 - subInstruction->param2);   
                break;
            }

            case Instruction::InstructionType::MUL :
            {
                auto mulInstruction = static_cast<Instruction::Mul*>(instruction.get());
                m_resultStack.push(mulInstruction->param1 * mulInstruction->param2);
                break;
            }

            case Instruction::InstructionType::DIV :
            {
                auto divInstruction = static_cast<Instruction::Div*>(instruction.get());
                m_resultStack.push(divInstruction->param1 / divInstruction->param2);
                break;
            }

            case Instruction::InstructionType::STORE :
            {
                auto storeInstruction = static_cast<Instruction::Store*>(instruction.get());
                m_resultStack.push(storeInstruction->param1);
                break;
            }

            case Instruction::InstructionType::CMP :
            {
                auto compareInstruction = static_cast<Instruction::Compare*>(instruction.get());
                Instruction::Compare::CompareOperand operand = compareInstruction->operand;
                
                switch(operand)
                {
                    case Instruction::Compare::CompareOperand::Greater :
                    {
                        m_resultStack.push(compareInstruction->param1 > compareInstruction->param2);
                        break;
                    }
                    
                    case Instruction::Compare::CompareOperand::Less :
                    {
                        m_resultStack.push(compareInstruction->param1 < compareInstruction->param2);
                        break;
                    }
                    
                    case Instruction::Compare::CompareOperand::Equal :
                    {
                        m_resultStack.push(compareInstruction->param1 == compareInstruction->param2);
                        break;
                    }
                    
                    case Instruction::Compare::CompareOperand::GreaterEqual :
                    {
                        m_resultStack.push(compareInstruction->param1 <= compareInstruction->param2);
                        break;
                    }
                    
                    case Instruction::Compare::CompareOperand::LessEqual :
                    {
                        m_resultStack.push(compareInstruction->param1 < compareInstruction->param2);
                        break;
                    }
                }
                break;
            }

            case Instruction::InstructionType::PRINT :
            {
                auto printInstruction = static_cast<Instruction::Print*>(instruction.get());
                std::cout << printInstruction->printStr << std::endl;
                break;
            }

            default :
            {
                break;
            }
        }
    }
}

void Interpreter::stop()
{
    m_running.store(false, std::memory_order_release);
}