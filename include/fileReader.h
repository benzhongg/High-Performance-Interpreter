#pragma once
#include <cstdint>
#include <fstream>
#include <memory>

class FileReader
{
private:
    std::ifstream m_iFstream;
    bool m_isReading { false };

public:
    FileReader(const std::string& filePath) : m_iFstream(filePath){};
    
    void start();
    void stop();
    
    std::uint32_t read();
};