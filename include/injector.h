#pragma once
//#include "HighPerformanceRingBuffer"

class Injector
{
    // rule of 5
public:
    Injector();
    void run(/*File input_file, HighPerformanceRingBuffer buffer*/);
    void stop();
};