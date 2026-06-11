#pragma once
#include <cstdint>
#include <fstream>
#include <memory>
#include <cstddef>
#include <cstring>
#include <type_traits>

// must be an abstract class
// usually when a class name is Base it implies abstract
class FileReaderBase
{
public:
    virtual std::uint32_t get_uint32 (bool* result = nullptr) = 0;
    virtual std::int32_t  get_int32  (bool* result = nullptr) = 0;
    virtual std::uint64_t get_uint64 (bool* result = nullptr) = 0;
    virtual std::int64_t  get_int64  (bool* result = nullptr) = 0;
    virtual std::uint8_t  get_uint8  (bool* result = nullptr) = 0;
    virtual std::int8_t   get_int8   (bool* result = nullptr) = 0;
    virtual char*         get_bytes  (size_t size, bool* result = nullptr) = 0;
};


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