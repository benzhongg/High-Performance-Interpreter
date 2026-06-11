#pragma once
#include <cstdint>
#include <fstream>
#include <memory>
#include <cstddef>
#include <cstring>
#include <type_traits>

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

class BufferFileReader : public FileReaderBase
{

private:
    const char* m_data;
    size_t m_size;
    size_t m_pos;
    
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
    BufferFileReader(const char* data, size_t size) : m_data(data), m_size(size), m_pos(0){}

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


