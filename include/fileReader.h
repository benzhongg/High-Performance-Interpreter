#pragma once
#include <cstdint>
#include <fstream>
#include <memory>
#include <vector>
#include <cstddef>
#include <cstring>
#include <type_traits>
#include <filesystem>
#include <expected>
#include "stream_utils.h"
#include <stdexcept>


enum ErrorCode
{
    NotFound,
    InvalidFormat
};
class FileReaderBase
{
public:
    FileReaderBase() = default;

    virtual std::uint32_t get_uint32 (bool* result = nullptr) = 0;
    virtual std::int32_t  get_int32  (bool* result = nullptr) = 0;
    virtual std::uint64_t get_uint64 (bool* result = nullptr) = 0;
    virtual std::int64_t  get_int64  (bool* result = nullptr) = 0;
    virtual std::uint8_t  get_uint8  (bool* result = nullptr) = 0;
    virtual std::int8_t   get_int8   (bool* result = nullptr) = 0;
    virtual char*         get_bytes  (size_t size, bool* result = nullptr) = 0;
};

class StreamFileReader : public FileReaderBase 
{
private:
    std::ifstream m_stream;
    
    
    StreamFileReader(const std::filesystem::path& path)
    {
        // we put std::ios::binary for what reason?
        m_stream.open(path, std::ios::binary);
    }
    
    template<typename T>
    bool getBytes(T& value, size_t length = 0) {
        // QUESTION -> WHY IS THIS ALLOWED?
        if (m_stream.read(reinterpret_cast<char*>(&value), sizeof(T)))
        {
            return true;;
        }

        return false;
    }

public:
    
    static std::expected<StreamFileReader, ErrorCode> create(const std::filesystem::path& path)
    {
        if (path.extension() != ".txt")
        {
            return std::unexpected(ErrorCode::InvalidFormat);
        }

        if (!std::filesystem::exists(path))
        {
            return std::unexpected(ErrorCode::NotFound);
        }


        return StreamFileReader(path);
    }

    std::uint32_t get_uint32 (bool* result = nullptr) override 
    {
        std::uint32_t value;
        bool success = getBytes<std::uint32_t>(value);
        if (!success) 
        {
            throw std::runtime_error("Could not open file");
        }
        return value;
    }

    std::int32_t get_int32 (bool* result = nullptr) override
    {

    }

    std::uint64_t get_uint64 (bool* result = nullptr) override
    {

    }

    std::int64_t get_int64 (bool* result = nullptr) override
    {

    }

    std::uint8_t get_uint8 (bool* result = nullptr) override
    {

    }

    std::int8_t get_int8 (bool* result = nullptr) override
    {

    }

    char* get_bytes(size_t size, bool* result = nullptr) override
    {
        char* res = new char[size];
        
        m_stream.read(res, size);

        return res;
    }
};



class BufferFileReader : public FileReaderBase
{

private:
    const char* m_data { nullptr };
    size_t m_size { 0 };
    size_t m_pos { 0 };
    std::vector<char> m_byteContainer {};

    template <typename T>
    T read_scalar(bool* result)
    {
        static_assert(std::is_integral_v<T>, "T must be an integral type");

        if (!can_read(sizeof(T)))
        {
            set_result(result, false);
            return T{};
        }

        T value{};
        std::memcpy(&value, m_data + m_pos, sizeof(T));
        m_pos += sizeof(T);

        set_result(result, true);
        return value;
    }

    bool can_read(size_t bytes) const
    {
        return m_pos + bytes <= m_size;
    }

    void set_result(bool* result, bool value)
    {
        if (result)
        *result = value;
    }

public:
    BufferFileReader(const char* data, size_t size) : FileReaderBase(), m_data(data), m_size(size), m_pos(0){}

    std::uint32_t get_uint32(bool* result = nullptr) override
    {
        return read_scalar<std::uint32_t>(result);
    }

    std::int32_t get_int32(bool* result = nullptr) override
    {
        return read_scalar<std::int32_t>(result);
    }

    std::uint64_t get_uint64(bool* result = nullptr) override
    {
        return read_scalar<std::uint64_t>(result);
    }

    std::int64_t get_int64(bool* result = nullptr) override
    {
        return read_scalar<std::int64_t>(result);
    }

    std::uint8_t get_uint8(bool* result = nullptr) override
    {
        return read_scalar<std::uint8_t>(result);
    }

    std::int8_t get_int8(bool* result = nullptr) override
    {
        return read_scalar<std::int8_t>(result);
    }

    char* get_bytes(size_t size, bool* result = nullptr) override
    {
        if (!can_read(size))
        {
            set_result(result, false);
            return nullptr;
        }

        char* out = new char[size];
        std::memcpy(out, m_data + m_pos, size);
        m_pos += size;

        set_result(result, true);
        return out;
    }

    size_t remaining() const
    {
        return m_size - m_pos;
    }

    size_t position() const
    {
        return m_pos;
    }

    void reset()
    {
        m_pos = 0;
    }
};