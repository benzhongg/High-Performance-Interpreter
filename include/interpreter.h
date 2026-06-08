#pragma once
//#include "hpringbuffer.h"

class Interpreter
{
public:
    Interpreter();
    void run(/*HighPerformanceRingBuffer, Execution Stack*/);
    void stop();
}