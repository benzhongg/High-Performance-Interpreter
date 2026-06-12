#include "interpreter.h"

Interpreter::Interpreter()
{

}

bool Interpreter::addInstruction(Instruction::Base inputInstruction)
{
    return m_ringBuffer->push(inputInstruction);
}

void Interpreter::run()
{
    //grabs from ringbuffer
    //executes instruction 
    //and 
    //pushes to stack 
}