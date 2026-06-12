#pragma once
#include "ringBuffer.h"

class Injector
{
public:
    Injector();
    void run(/*File input_file, HighPerformanceRingBuffer buffer*/);
    void stop();
};




