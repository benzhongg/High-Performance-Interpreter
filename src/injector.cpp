#include "injector.h"

Injector::Injector(std::shared_ptr<FileReaderBase> fileReader, InstructionRingBuffer1KPtr buffer) : m_fileReader(fileReader), m_ringBuffer(buffer)
{
    m_instructBuilder = std::make_unique<InstructionBuilder>(InstructionBuilder(fileReader));
}

void Injector::runAsync()
{
    m_thread = std::thread(&Injector::run, this);
}

void Injector::run()
{
    m_running = true;
    
    while (m_running)
    {
        auto resInstruction = m_instructBuilder->get_instruction();

        if (!resInstruction) { continue; }

        while(!m_ringBuffer->push(resInstruction) && m_running)
        {
            std::this_thread::yield();
        }
    }
}

void Injector::stop()
{
    m_running = false;
    m_thread.join(); 
}