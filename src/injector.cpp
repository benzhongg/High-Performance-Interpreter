#include "injector.h"

Injector::Injector(FileReaderBase* fileReader, RingBuffer<std::shared_ptr<Instruction::Base>, 1024>* buffer)
: m_fileReader(fileReader), m_ringBuffer(buffer)
{
    m_instructBuilder = new InstructionBuilder(fileReader);
}

void Injector::run()
{
    while (true)
    {
        auto resInstruction = m_instructBuilder->get_instruction();
        
        while(!m_ringBuffer->push(resInstruction))
        {
            std::this_thread::yield();
        }
    }
}

void Injector::stop()
{
    // TODO: on your as exercise
}