#pragma once
#include <array>
#include <list>
#include <iostream>
#include <stdexcept>
#include <atomic>
#include <thread>


template<typename T, size_t CAPACITY>
class RingBuffer
{
private:
    std::array<T, CAPACITY> m_buffer { default_value() };
    // things to note
        // False Sharing -> if head and tail are atomics and placed next to each other in mem
        // They may end up on the same cache line, meaning either one of them might invalidate
            // the other for trying to read/update
            // this can be solved through "padding" like a char padding[64]
            
    //head is next write
    std::atomic<int> m_head { 0 };
    
    //tail is next read
    std::atomic<int> m_tail { 0 };

protected:
    T default_value()
    {
        return T{};
    }
    
public:
    bool isFull()
    {
        return size() + 1 == CAPACITY;    
    }
    
    bool isEmpty()
    {
        return size() == 0;
    }
    
    RingBuffer() = default;
    
    ~RingBuffer() = default;

    bool push(T v)
    { 
        
        if (!isFull())
        {
            // acquires all memory published before this point by other threads -> making it available to us
            // releases all updates and publishes all changes made to other threads
            
            // x86 coherent cache model

            auto temp_head = m_head.load(std::memory_order_acquire);
            
            m_buffer[temp_head] = v;

            temp_head = (temp_head + 1) % CAPACITY;
            
            // Releasing the most up to date m_head is necessary
            m_head.store(temp_head, std::memory_order_release);
            
            return true;
        } 
        else 
        {
            return false;
        }
    }
    
    bool pop(T& out_value)
    {
        
        if (isEmpty())
        {
            return false;
        }
        
        auto temp_tail = m_tail.load(std::memory_order_acquire);
        
        out_value = m_buffer[temp_tail];
        temp_tail = (temp_tail + 1) % CAPACITY;
        
        m_tail.store(temp_tail, std::memory_order_release);

        return true;
    }
    
    
    size_t size() const
    {

        // acquire is needed to check the up to date m_head + m_tail value
        auto temp_head = m_head.load(std::memory_order_acquire);
        auto temp_tail = m_tail.load(std::memory_order_acquire);

        if (temp_tail < temp_head){
            return temp_head - temp_tail;
        }
        
        if (temp_head < temp_tail){
            return CAPACITY - temp_tail + temp_head;
        }
        
        return 0;
    }
    
    void clear()
    {
        m_tail.store(0, std::memory_order_release);
        m_head.store(0, std::memory_order_release);
    }
    
    size_t capacity()
    {
        return CAPACITY - 1;
    }
};