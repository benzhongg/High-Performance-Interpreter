#include "fileReader.h"

void FileReader::start()
{
    m_isReading = true;
}

void FileReader::stop()
{
    m_isReading = false;
}

std::uint32_t FileReader::read()
{
    std::uint32_t resultingByteCode = 0;
    
    m_iFstream >> resultingByteCode;

    return resultingByteCode;
}
    